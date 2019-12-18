#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct purgatory_info {TYPE_2__* sechdrs; void* purgatory_buf; TYPE_1__* ehdr; } ;
struct TYPE_13__ {unsigned long r_offset; int /*<<< orphan*/  r_info; scalar_t__ r_addend; } ;
struct TYPE_12__ {int sh_offset; int sh_size; unsigned long sh_addr; } ;
struct TYPE_11__ {size_t st_shndx; unsigned long st_value; } ;
struct TYPE_10__ {scalar_t__ sh_addr; } ;
struct TYPE_9__ {size_t e_shnum; } ;
typedef  TYPE_3__ Elf_Sym ;
typedef  TYPE_4__ Elf_Shdr ;
typedef  TYPE_5__ Elf_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  ELF64_R_SYM (int /*<<< orphan*/ ) ; 
 int ELF64_R_TYPE (int /*<<< orphan*/ ) ; 
 int ENOEXEC ; 
 size_t SHN_ABS ; 
 size_t SHN_COMMON ; 
 size_t SHN_UNDEF ; 
 int /*<<< orphan*/  arch_kexec_do_relocs (int,void*,unsigned long,unsigned long) ; 

int arch_kexec_apply_relocations_add(struct purgatory_info *pi,
				     Elf_Shdr *section,
				     const Elf_Shdr *relsec,
				     const Elf_Shdr *symtab)
{
	Elf_Rela *relas;
	int i, r_type;

	relas = (void *)pi->ehdr + relsec->sh_offset;

	for (i = 0; i < relsec->sh_size / sizeof(*relas); i++) {
		const Elf_Sym *sym;	/* symbol to relocate */
		unsigned long addr;	/* final location after relocation */
		unsigned long val;	/* relocated symbol value */
		void *loc;		/* tmp location to modify */

		sym = (void *)pi->ehdr + symtab->sh_offset;
		sym += ELF64_R_SYM(relas[i].r_info);

		if (sym->st_shndx == SHN_UNDEF)
			return -ENOEXEC;

		if (sym->st_shndx == SHN_COMMON)
			return -ENOEXEC;

		if (sym->st_shndx >= pi->ehdr->e_shnum &&
		    sym->st_shndx != SHN_ABS)
			return -ENOEXEC;

		loc = pi->purgatory_buf;
		loc += section->sh_offset;
		loc += relas[i].r_offset;

		val = sym->st_value;
		if (sym->st_shndx != SHN_ABS)
			val += pi->sechdrs[sym->st_shndx].sh_addr;
		val += relas[i].r_addend;

		addr = section->sh_addr + relas[i].r_offset;

		r_type = ELF64_R_TYPE(relas[i].r_info);
		arch_kexec_do_relocs(r_type, loc, val, addr);
	}
	return 0;
}