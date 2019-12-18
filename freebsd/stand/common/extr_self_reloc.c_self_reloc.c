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
typedef  scalar_t__ Elf_Word ;
typedef  scalar_t__ Elf_Addr ;
typedef  TYPE_2__ ElfW_Rel ;
typedef  TYPE_3__ ElfW_Dyn ;

/* Variables and functions */
 int DT_NULL ; 
#define  DT_REL 135 
#define  DT_RELA 134 
#define  DT_RELAENT 133 
#define  DT_RELASZ 132 
#define  DT_RELENT 131 
#define  DT_RELSZ 130 
 int ELFW_R_TYPE (int /*<<< orphan*/ ) ; 
#define  RELOC_TYPE_NONE 129 
#define  RELOC_TYPE_RELATIVE 128 

void
self_reloc(Elf_Addr baseaddr, ElfW_Dyn *dynamic)
{
	Elf_Word relsz, relent;
	Elf_Addr *newaddr;
	ElfW_Rel *rel;
	ElfW_Dyn *dynp;

	/*
	 * Find the relocation address, its size and the relocation entry.
	 */
	relsz = 0;
	relent = 0;
	for (dynp = dynamic; dynp->d_tag != DT_NULL; dynp++) {
		switch (dynp->d_tag) {
		case DT_REL:
		case DT_RELA:
			rel = (ElfW_Rel *)(dynp->d_un.d_ptr + baseaddr);
			break;
		case DT_RELSZ:
		case DT_RELASZ:
			relsz = dynp->d_un.d_val;
			break;
		case DT_RELENT:
		case DT_RELAENT:
			relent = dynp->d_un.d_val;
			break;
		default:
			break;
		}
	}

	/*
	 * Perform the actual relocation. We rely on the object having been
	 * linked at 0, so that the difference between the load and link
	 * address is the same as the load address.
	 */
	for (; relsz > 0; relsz -= relent) {
		switch (ELFW_R_TYPE(rel->r_info)) {
		case RELOC_TYPE_NONE:
			/* No relocation needs be performed. */
			break;

		case RELOC_TYPE_RELATIVE:
			newaddr = (Elf_Addr *)(rel->r_offset + baseaddr);
#ifdef ELF_RELA
			/* Addend relative to the base address. */
			*newaddr = baseaddr + rel->r_addend;
#else
			/* Address relative to the base address. */
			*newaddr += baseaddr;
#endif
			break;
		default:
			/* XXX: do we need other relocations ? */
			break;
		}
		rel = (ElfW_Rel *)(void *)((caddr_t) rel + relent);
	}
}