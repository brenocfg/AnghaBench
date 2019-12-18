#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ caddr_t ;
struct TYPE_5__ {scalar_t__ d_val; scalar_t__ d_ptr; } ;
struct TYPE_7__ {int d_tag; TYPE_1__ d_un; } ;
struct TYPE_6__ {scalar_t__ r_addend; scalar_t__ r_offset; int /*<<< orphan*/  r_info; } ;
typedef  TYPE_2__ Elf_Rela ;
typedef  TYPE_3__ Elf_Dyn ;
typedef  scalar_t__ Elf_Addr ;

/* Variables and functions */
 int DT_NULL ; 
#define  DT_RELA 129 
#define  DT_RELASZ 128 
 scalar_t__ ELF_R_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ R_PPC_RELATIVE ; 

void
elf_reloc_self(Elf_Dyn *dynp, Elf_Addr relocbase)
{
	Elf_Rela *rela = NULL, *relalim;
	Elf_Addr relasz = 0;
	Elf_Addr *where;

	/*
	 * Extract the rela/relasz values from the dynamic section
	 */
	for (; dynp->d_tag != DT_NULL; dynp++) {
		switch (dynp->d_tag) {
		case DT_RELA:
			rela = (Elf_Rela *)(relocbase+dynp->d_un.d_ptr);
			break;
		case DT_RELASZ:
			relasz = dynp->d_un.d_val;
			break;
		}
	}

	/*
	 * Relocate these values
	 */
	relalim = (Elf_Rela *)((caddr_t)rela + relasz);
	for (; rela < relalim; rela++) {
		if (ELF_R_TYPE(rela->r_info) != R_PPC_RELATIVE)
			continue;
		where = (Elf_Addr *)(relocbase + rela->r_offset);
		*where = (Elf_Addr)(relocbase + rela->r_addend);
	}
}