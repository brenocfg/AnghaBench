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
struct dl_phdr_info {int dlpi_phnum; uintptr_t dlpi_addr; TYPE_1__* dlpi_phdr; } ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_2__ {scalar_t__ p_type; int p_flags; uintptr_t p_vaddr; uintptr_t p_memsz; } ;
typedef  TYPE_1__ Elf_Phdr ;

/* Variables and functions */
 int PF_X ; 
 scalar_t__ PT_LOAD ; 

int
__elf_phdr_match_addr(struct dl_phdr_info *phdr_info, void *addr)
{
	const Elf_Phdr *ph;
	int i;

	for (i = 0; i < phdr_info->dlpi_phnum; i++) {
		ph = &phdr_info->dlpi_phdr[i];
		if (ph->p_type != PT_LOAD)
			continue;

		/* ELFv1 ABI for powerpc64 passes function descriptor
		 * pointers around, not function pointers.  The function
		 * descriptors live in .opd, which is a non-executable segment.
		 * The PF_X check would therefore make all address checks fail,
		 * causing a crash in some instances.  Don't skip over
		 * non-executable segments in the ELFv1 powerpc64 case.
		 */
#if !defined(__powerpc64__) || (defined(_CALL_ELF) && _CALL_ELF == 2)
		if ((ph->p_flags & PF_X) == 0)
			continue;
#endif

		if (phdr_info->dlpi_addr + ph->p_vaddr <= (uintptr_t)addr &&
		    (uintptr_t)addr + sizeof(addr) < phdr_info->dlpi_addr +
		    ph->p_vaddr + ph->p_memsz)
			break;
	}
	return (i != phdr_info->dlpi_phnum);
}