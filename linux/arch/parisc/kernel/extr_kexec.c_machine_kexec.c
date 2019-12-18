#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kimage_arch {unsigned long cmdline; unsigned long initrd_start; unsigned long initrd_end; } ;
struct kimage {unsigned long head; unsigned long start; struct kimage_arch arch; int /*<<< orphan*/  control_code_page; } ;
struct TYPE_4__ {unsigned long mem_free; } ;
struct TYPE_3__ {long long addr; } ;
typedef  TYPE_1__ Elf64_Fdesc ;

/* Variables and functions */
 int /*<<< orphan*/  FIX_TEXT_KEXEC ; 
 TYPE_2__* PAGE0 ; 
 unsigned long PAGE_MASK ; 
 scalar_t__ __fix_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dereference_function_descriptor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_cache_all () ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 int kexec_cmdline_offset ; 
 int kexec_free_mem_offset ; 
 int kexec_initrd_end_offset ; 
 int kexec_initrd_start_offset ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relocate_new_kernel ; 
 int /*<<< orphan*/  relocate_new_kernel_size ; 
 int /*<<< orphan*/  set_fixmap (int /*<<< orphan*/ ,unsigned long) ; 

void machine_kexec(struct kimage *image)
{
#ifdef CONFIG_64BIT
	Elf64_Fdesc desc;
#endif
	void (*reloc)(unsigned long head,
		      unsigned long start,
		      unsigned long phys);

	unsigned long phys = page_to_phys(image->control_code_page);
	void *virt = (void *)__fix_to_virt(FIX_TEXT_KEXEC);
	struct kimage_arch *arch = &image->arch;

	set_fixmap(FIX_TEXT_KEXEC, phys);

	flush_cache_all();

#ifdef CONFIG_64BIT
	reloc = (void *)&desc;
	desc.addr = (long long)virt;
#else
	reloc = (void *)virt;
#endif

	memcpy(virt, dereference_function_descriptor(relocate_new_kernel),
		relocate_new_kernel_size);

	*(unsigned long *)(virt + kexec_cmdline_offset) = arch->cmdline;
	*(unsigned long *)(virt + kexec_initrd_start_offset) = arch->initrd_start;
	*(unsigned long *)(virt + kexec_initrd_end_offset) = arch->initrd_end;
	*(unsigned long *)(virt + kexec_free_mem_offset) = PAGE0->mem_free;

	flush_cache_all();
	flush_tlb_all();
	local_irq_disable();

	reloc(image->head & PAGE_MASK, image->start, phys);
}