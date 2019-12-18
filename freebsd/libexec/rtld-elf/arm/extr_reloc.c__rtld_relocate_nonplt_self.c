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
typedef  int uint32_t ;
struct TYPE_5__ {int d_ptr; int d_val; } ;
struct TYPE_7__ {int d_tag; TYPE_1__ d_un; } ;
struct TYPE_6__ {int r_offset; } ;
typedef  TYPE_2__ Elf_Rel ;
typedef  TYPE_3__ Elf_Dyn ;
typedef  int Elf_Addr ;

/* Variables and functions */
 int DT_NULL ; 
#define  DT_REL 129 
#define  DT_RELSZ 128 

void
_rtld_relocate_nonplt_self(Elf_Dyn *dynp, Elf_Addr relocbase)
{
	const Elf_Rel *rel = NULL, *rellim;
	Elf_Addr relsz = 0;
	Elf_Addr *where;
	uint32_t size;

	for (; dynp->d_tag != DT_NULL; dynp++) {
		switch (dynp->d_tag) {
		case DT_REL:
			rel = (const Elf_Rel *)(relocbase + dynp->d_un.d_ptr);
			break;
		case DT_RELSZ:
			relsz = dynp->d_un.d_val;
			break;
		}
	}
	rellim = (const Elf_Rel *)((const char *)rel + relsz);
	size = (rellim - 1)->r_offset - rel->r_offset;
	for (; rel < rellim; rel++) {
		where = (Elf_Addr *)(relocbase + rel->r_offset);
		
		*where += (Elf_Addr)relocbase;
	}
}