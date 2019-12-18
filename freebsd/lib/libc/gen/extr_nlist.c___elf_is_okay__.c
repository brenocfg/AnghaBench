#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__* e_ident; scalar_t__ e_machine; scalar_t__ e_version; } ;
typedef  TYPE_1__ Elf_Ehdr ;

/* Variables and functions */
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 size_t EI_VERSION ; 
 scalar_t__ ELF_TARG_CLASS ; 
 scalar_t__ ELF_TARG_DATA ; 
 scalar_t__ ELF_TARG_MACH ; 
 scalar_t__ ELF_TARG_VER ; 
 scalar_t__ IS_ELF (TYPE_1__) ; 

int
__elf_is_okay__(Elf_Ehdr *ehdr)
{
	int retval = 0;
	/*
	 * We need to check magic, class size, endianess,
	 * and version before we look at the rest of the
	 * Elf_Ehdr structure.  These few elements are
	 * represented in a machine independant fashion.
	 */
	if (IS_ELF(*ehdr) &&
	    ehdr->e_ident[EI_CLASS] == ELF_TARG_CLASS &&
	    ehdr->e_ident[EI_DATA] == ELF_TARG_DATA &&
	    ehdr->e_ident[EI_VERSION] == ELF_TARG_VER) {

		/* Now check the machine dependant header */
		if (ehdr->e_machine == ELF_TARG_MACH &&
		    ehdr->e_version == ELF_TARG_VER)
			retval = 1;
	}
	return retval;
}