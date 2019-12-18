#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elfhdr {int e_phnum; scalar_t__ e_phoff; } ;
struct elf_phdr {scalar_t__ p_type; scalar_t__ p_paddr; scalar_t__ p_offset; scalar_t__ p_filesz; } ;
struct coredump_params {int dummy; } ;
typedef  int /*<<< orphan*/  phdr ;
typedef  scalar_t__ loff_t ;
typedef  scalar_t__ Elf32_Off ;

/* Variables and functions */
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  dump_emit (struct coredump_params*,struct elf_phdr*,int) ; 
 scalar_t__ vsyscall_ehdr ; 

int elf_core_write_extra_phdrs(struct coredump_params *cprm, loff_t offset)
{
	if ( vsyscall_ehdr ) {
		const struct elfhdr *const ehdrp =
			(struct elfhdr *) vsyscall_ehdr;
		const struct elf_phdr *const phdrp =
			(const struct elf_phdr *) (vsyscall_ehdr + ehdrp->e_phoff);
		int i;
		Elf32_Off ofs = 0;

		for (i = 0; i < ehdrp->e_phnum; ++i) {
			struct elf_phdr phdr = phdrp[i];

			if (phdr.p_type == PT_LOAD) {
				ofs = phdr.p_offset = offset;
				offset += phdr.p_filesz;
			} else {
				phdr.p_offset += ofs;
			}
			phdr.p_paddr = 0; /* match other core phdrs */
			if (!dump_emit(cprm, &phdr, sizeof(phdr)))
				return 0;
		}
	}
	return 1;
}