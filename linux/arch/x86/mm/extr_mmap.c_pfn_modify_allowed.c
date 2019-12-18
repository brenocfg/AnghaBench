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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  X86_BUG_L1TF ; 
 int /*<<< orphan*/  __pte_needs_invert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boot_cpu_has_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 unsigned long l1tf_pfn_limit () ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int /*<<< orphan*/  pgprot_val (int /*<<< orphan*/ ) ; 

bool pfn_modify_allowed(unsigned long pfn, pgprot_t prot)
{
	if (!boot_cpu_has_bug(X86_BUG_L1TF))
		return true;
	if (!__pte_needs_invert(pgprot_val(prot)))
		return true;
	/* If it's real memory always allow */
	if (pfn_valid(pfn))
		return true;
	if (pfn >= l1tf_pfn_limit() && !capable(CAP_SYS_ADMIN))
		return false;
	return true;
}