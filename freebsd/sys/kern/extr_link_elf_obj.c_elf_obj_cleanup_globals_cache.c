#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* elf_file_t ;
struct TYPE_5__ {scalar_t__ st_shndx; scalar_t__ st_value; } ;
struct TYPE_4__ {scalar_t__ ddbsymcnt; TYPE_2__* ddbsymtab; } ;
typedef  TYPE_2__ Elf_Sym ;
typedef  scalar_t__ Elf_Size ;

/* Variables and functions */
 scalar_t__ SHN_FBSD_CACHED ; 
 scalar_t__ SHN_UNDEF ; 

__attribute__((used)) static void
elf_obj_cleanup_globals_cache(elf_file_t ef)
{
	Elf_Sym *sym;
	Elf_Size i;

	for (i = 0; i < ef->ddbsymcnt; i++) {
		sym = ef->ddbsymtab + i;
		if (sym->st_shndx == SHN_FBSD_CACHED) {
			sym->st_shndx = SHN_UNDEF;
			sym->st_value = 0;
		}
	}
}