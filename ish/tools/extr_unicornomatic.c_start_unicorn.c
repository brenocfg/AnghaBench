#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uc_hook ;
typedef  int /*<<< orphan*/  uc_engine ;
struct pt_entry {int flags; int offset; TYPE_1__* data; } ;
struct mem {int dummy; } ;
struct cpu_state {int /*<<< orphan*/  fcw; int /*<<< orphan*/  eflags; int /*<<< orphan*/  eip; int /*<<< orphan*/  esp; } ;
typedef  int page_t ;
typedef  int addr_t ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 int MEM_PAGES ; 
 int PAGE_BITS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int P_WRITE ; 
 int /*<<< orphan*/  UC_ARCH_X86 ; 
 int /*<<< orphan*/  UC_HOOK_INTR ; 
 int /*<<< orphan*/  UC_HOOK_MEM_UNMAPPED ; 
 int /*<<< orphan*/  UC_MODE_32 ; 
 int UC_PROT_EXEC ; 
 int UC_PROT_READ ; 
 int UC_PROT_WRITE ; 
 int /*<<< orphan*/  UC_X86_REG_EFLAGS ; 
 int /*<<< orphan*/  UC_X86_REG_EIP ; 
 int /*<<< orphan*/  UC_X86_REG_ESP ; 
 int /*<<< orphan*/  UC_X86_REG_FPCW ; 
 struct pt_entry* mem_pt (struct mem*,int) ; 
 int /*<<< orphan*/  setup_gdt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uc_hook_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_interrupt_callback ; 
 int /*<<< orphan*/  uc_mem_map (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uc_mem_write (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  uc_setreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uc_trycall (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uc_unmapped_callback ; 

uc_engine *start_unicorn(struct cpu_state *cpu, struct mem *mem) {
    uc_engine *uc;
    uc_trycall(uc_open(UC_ARCH_X86, UC_MODE_32, &uc), "uc_open");

    // copy registers
    uc_setreg(uc, UC_X86_REG_ESP, cpu->esp);
    uc_setreg(uc, UC_X86_REG_EIP, cpu->eip);
    uc_setreg(uc, UC_X86_REG_EFLAGS, cpu->eflags);
    uc_setreg(uc, UC_X86_REG_FPCW, cpu->fcw);

    // copy memory
    // XXX unicorn has a ?bug? where setting up 334 mappings takes five
    // seconds on my raspi. it seems to be accidentally quadratic (dot tumblr dot com)
    for (page_t page = 0; page < MEM_PAGES; page++) {
        struct pt_entry *pt = mem_pt(mem, page);
        if (pt == NULL)
            continue;
        int prot = UC_PROT_READ | UC_PROT_EXEC;
        // really only the write bit is meaningful (FIXME)
        if (pt->flags & P_WRITE) prot |= UC_PROT_WRITE;
        addr_t addr = page << PAGE_BITS;
        void *data = pt->data->data + pt->offset;
        uc_trycall(uc_mem_map(uc, addr, PAGE_SIZE, prot), "uc_mem_map");
        uc_trycall(uc_mem_write(uc, addr, data, PAGE_SIZE), "uc_mem_write");
    }

    // set up some sort of gdt, because we need gs to work for thread locals
    setup_gdt(uc);

    // set up exception handler
    uc_hook hook;
    uc_trycall(uc_hook_add(uc, &hook, UC_HOOK_INTR, uc_interrupt_callback, NULL, 1, 0), "uc_hook_add");
    uc_trycall(uc_hook_add(uc, &hook, UC_HOOK_MEM_UNMAPPED, uc_unmapped_callback, NULL, 1, 0), "uc_hook_add");

    return uc;
}