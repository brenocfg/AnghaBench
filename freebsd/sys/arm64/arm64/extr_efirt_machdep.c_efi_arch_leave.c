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
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcast_tlbi_workaround ; 
 int /*<<< orphan*/  curpmap ; 
 int /*<<< orphan*/  invalidate_local_icache () ; 
 int /*<<< orphan*/  pmap_to_ttbr0 (scalar_t__) ; 
 int /*<<< orphan*/  set_ttbr0 (int /*<<< orphan*/ ) ; 

void
efi_arch_leave(void)
{

	/*
	 * Restore the pcpu pointer. Some UEFI implementations trash it and
	 * we don't store it before calling into them. To fix this we need
	 * to restore it after returning to the kernel context. As reading
	 * curpmap will access x18 we need to restore it before loading
	 * the pmap pointer.
	 */
	__asm __volatile(
	    "mrs x18, tpidr_el1	\n"
	);
	set_ttbr0(pmap_to_ttbr0(PCPU_GET(curpmap)));
	if (PCPU_GET(bcast_tlbi_workaround) != 0)
		invalidate_local_icache();
}