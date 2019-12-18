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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ Elf_Size ;

/* Variables and functions */
 scalar_t__ kstrtab ; 
 scalar_t__ ksymtab ; 
 scalar_t__ ksymtab_size ; 

int
db_fetch_ksymtab(vm_offset_t ksym_start, vm_offset_t ksym_end)
{
	Elf_Size strsz;

	if (ksym_end > ksym_start && ksym_start != 0) {
		ksymtab = ksym_start;
		ksymtab_size = *(Elf_Size*)ksymtab;
		ksymtab += sizeof(Elf_Size);
		kstrtab = ksymtab + ksymtab_size;
		strsz = *(Elf_Size*)kstrtab;
		kstrtab += sizeof(Elf_Size);
		if (kstrtab + strsz > ksym_end) {
			/* Sizes doesn't match, unset everything. */
			ksymtab = ksymtab_size = kstrtab = 0;
		}
	}

	if (ksymtab == 0 || ksymtab_size == 0 || kstrtab == 0)
		return (-1);

	return (0);
}