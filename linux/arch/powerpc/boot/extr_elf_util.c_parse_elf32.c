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
struct elf_info {int /*<<< orphan*/  elfoffset; int /*<<< orphan*/  memsize; int /*<<< orphan*/  loadsize; } ;
struct TYPE_4__ {scalar_t__* e_ident; scalar_t__ e_type; scalar_t__ e_machine; unsigned int e_phnum; scalar_t__ e_phoff; } ;
struct TYPE_3__ {scalar_t__ p_type; int /*<<< orphan*/  p_offset; int /*<<< orphan*/  p_memsz; int /*<<< orphan*/  p_filesz; } ;
typedef  TYPE_1__ Elf32_Phdr ;
typedef  TYPE_2__ Elf32_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_MAG0 ; 
 size_t EI_MAG1 ; 
 size_t EI_MAG2 ; 
 size_t EI_MAG3 ; 
 scalar_t__ ELFCLASS32 ; 
 scalar_t__ ELFDATA2MSB ; 
 scalar_t__ ELFMAG0 ; 
 scalar_t__ ELFMAG1 ; 
 scalar_t__ ELFMAG2 ; 
 scalar_t__ ELFMAG3 ; 
 scalar_t__ EM_PPC ; 
 scalar_t__ ET_DYN ; 
 scalar_t__ ET_EXEC ; 
 scalar_t__ PT_LOAD ; 

int parse_elf32(void *hdr, struct elf_info *info)
{
	Elf32_Ehdr *elf32 = hdr;
	Elf32_Phdr *elf32ph;
	unsigned int i;

	if (!(elf32->e_ident[EI_MAG0]  == ELFMAG0	&&
	      elf32->e_ident[EI_MAG1]  == ELFMAG1	&&
	      elf32->e_ident[EI_MAG2]  == ELFMAG2	&&
	      elf32->e_ident[EI_MAG3]  == ELFMAG3	&&
	      elf32->e_ident[EI_CLASS] == ELFCLASS32	&&
	      elf32->e_ident[EI_DATA]  == ELFDATA2MSB	&&
	      (elf32->e_type            == ET_EXEC ||
	       elf32->e_type            == ET_DYN)      &&
	      elf32->e_machine         == EM_PPC))
		return 0;

	elf32ph = (Elf32_Phdr *) ((unsigned long)elf32 + elf32->e_phoff);
	for (i = 0; i < elf32->e_phnum; i++, elf32ph++)
		if (elf32ph->p_type == PT_LOAD)
			break;
	if (i >= elf32->e_phnum)
		return 0;

	info->loadsize = elf32ph->p_filesz;
	info->memsize = elf32ph->p_memsz;
	info->elfoffset = elf32ph->p_offset;
	return 1;
}