#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
struct elfhdr {int /*<<< orphan*/  e_phnum; } ;
struct elf_phdr {int p_flags; unsigned long p_vaddr; unsigned long long p_offset; unsigned long long p_paddr; unsigned long long p_filesz; unsigned long long p_memsz; scalar_t__ p_align; void* p_type; } ;
struct TYPE_6__ {int mem_range_cnt; TYPE_1__* mem_ranges; } ;
struct TYPE_5__ {unsigned long long* boot_mem_addr; unsigned long long boot_mem_dest_addr; int boot_mem_regs_cnt; scalar_t__* boot_mem_sz; } ;
struct TYPE_4__ {unsigned long long base; unsigned long long size; } ;

/* Variables and functions */
 int PF_R ; 
 int PF_W ; 
 int PF_X ; 
 void* PT_LOAD ; 
 void* PT_NOTE ; 
 unsigned long long VMCOREINFO_NOTE_SIZE ; 
 scalar_t__ __va (unsigned long long) ; 
 TYPE_3__ crash_mrange_info ; 
 int /*<<< orphan*/  fadump_init_elfcore_header (char*) ; 
 unsigned long long fadump_relocate (int /*<<< orphan*/ ) ; 
 TYPE_2__ fw_dump ; 
 int /*<<< orphan*/  paddr_vmcoreinfo_note () ; 

__attribute__((used)) static int fadump_create_elfcore_headers(char *bufp)
{
	unsigned long long raddr, offset;
	struct elf_phdr *phdr;
	struct elfhdr *elf;
	int i, j;

	fadump_init_elfcore_header(bufp);
	elf = (struct elfhdr *)bufp;
	bufp += sizeof(struct elfhdr);

	/*
	 * setup ELF PT_NOTE, place holder for cpu notes info. The notes info
	 * will be populated during second kernel boot after crash. Hence
	 * this PT_NOTE will always be the first elf note.
	 *
	 * NOTE: Any new ELF note addition should be placed after this note.
	 */
	phdr = (struct elf_phdr *)bufp;
	bufp += sizeof(struct elf_phdr);
	phdr->p_type = PT_NOTE;
	phdr->p_flags = 0;
	phdr->p_vaddr = 0;
	phdr->p_align = 0;

	phdr->p_offset = 0;
	phdr->p_paddr = 0;
	phdr->p_filesz = 0;
	phdr->p_memsz = 0;

	(elf->e_phnum)++;

	/* setup ELF PT_NOTE for vmcoreinfo */
	phdr = (struct elf_phdr *)bufp;
	bufp += sizeof(struct elf_phdr);
	phdr->p_type	= PT_NOTE;
	phdr->p_flags	= 0;
	phdr->p_vaddr	= 0;
	phdr->p_align	= 0;

	phdr->p_paddr	= fadump_relocate(paddr_vmcoreinfo_note());
	phdr->p_offset	= phdr->p_paddr;
	phdr->p_memsz	= phdr->p_filesz = VMCOREINFO_NOTE_SIZE;

	/* Increment number of program headers. */
	(elf->e_phnum)++;

	/* setup PT_LOAD sections. */
	j = 0;
	offset = 0;
	raddr = fw_dump.boot_mem_addr[0];
	for (i = 0; i < crash_mrange_info.mem_range_cnt; i++) {
		u64 mbase, msize;

		mbase = crash_mrange_info.mem_ranges[i].base;
		msize = crash_mrange_info.mem_ranges[i].size;
		if (!msize)
			continue;

		phdr = (struct elf_phdr *)bufp;
		bufp += sizeof(struct elf_phdr);
		phdr->p_type	= PT_LOAD;
		phdr->p_flags	= PF_R|PF_W|PF_X;
		phdr->p_offset	= mbase;

		if (mbase == raddr) {
			/*
			 * The entire real memory region will be moved by
			 * firmware to the specified destination_address.
			 * Hence set the correct offset.
			 */
			phdr->p_offset = fw_dump.boot_mem_dest_addr + offset;
			if (j < (fw_dump.boot_mem_regs_cnt - 1)) {
				offset += fw_dump.boot_mem_sz[j];
				raddr = fw_dump.boot_mem_addr[++j];
			}
		}

		phdr->p_paddr = mbase;
		phdr->p_vaddr = (unsigned long)__va(mbase);
		phdr->p_filesz = msize;
		phdr->p_memsz = msize;
		phdr->p_align = 0;

		/* Increment number of program headers. */
		(elf->e_phnum)++;
	}
	return 0;
}