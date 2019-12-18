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

/* Variables and functions */
 int /*<<< orphan*/  CRITICAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcast_tlbi_workaround ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  efi_ttbr0 ; 
 int /*<<< orphan*/  invalidate_local_icache () ; 
 int /*<<< orphan*/  set_ttbr0 (int /*<<< orphan*/ ) ; 

int
efi_arch_enter(void)
{

	CRITICAL_ASSERT(curthread);

	/*
	 * Temporarily switch to EFI's page table.  However, we leave curpmap
	 * unchanged in order to prevent its ASID from being reclaimed before
	 * we switch back to its page table in efi_arch_leave().
	 */
	set_ttbr0(efi_ttbr0);
	if (PCPU_GET(bcast_tlbi_workaround) != 0)
		invalidate_local_icache();

	return (0);
}