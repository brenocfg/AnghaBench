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
struct elf_phdr {scalar_t__ p_type; scalar_t__ p_paddr; scalar_t__ p_offset; scalar_t__ p_filesz; scalar_t__ p_memsz; } ;
struct coredump_params {int dummy; } ;
typedef  int /*<<< orphan*/  phdr ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int e_phnum; scalar_t__ e_phoff; } ;
typedef  scalar_t__ Elf64_Off ;

/* Variables and functions */
 scalar_t__ GATE_ADDR ; 
 TYPE_1__* GATE_EHDR ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ PT_LOAD ; 
 int /*<<< orphan*/  dump_emit (struct coredump_params*,struct elf_phdr*,int) ; 

int elf_core_write_extra_phdrs(struct coredump_params *cprm, loff_t offset)
{
	const struct elf_phdr *const gate_phdrs =
		(const struct elf_phdr *) (GATE_ADDR + GATE_EHDR->e_phoff);
	int i;
	Elf64_Off ofs = 0;

	for (i = 0; i < GATE_EHDR->e_phnum; ++i) {
		struct elf_phdr phdr = gate_phdrs[i];

		if (phdr.p_type == PT_LOAD) {
			phdr.p_memsz = PAGE_ALIGN(phdr.p_memsz);
			phdr.p_filesz = phdr.p_memsz;
			if (ofs == 0) {
				ofs = phdr.p_offset = offset;
				offset += phdr.p_filesz;
			} else {
				phdr.p_offset = ofs;
			}
		} else {
			phdr.p_offset += ofs;
		}
		phdr.p_paddr = 0; /* match other core phdrs */
		if (!dump_emit(cprm, &phdr, sizeof(phdr)))
			return 0;
	}
	return 1;
}