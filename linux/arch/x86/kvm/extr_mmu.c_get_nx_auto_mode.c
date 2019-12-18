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
 int /*<<< orphan*/  X86_BUG_ITLB_MULTIHIT ; 
 scalar_t__ boot_cpu_has_bug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_mitigations_off () ; 

__attribute__((used)) static bool get_nx_auto_mode(void)
{
	/* Return true when CPU has the bug, and mitigations are ON */
	return boot_cpu_has_bug(X86_BUG_ITLB_MULTIHIT) && !cpu_mitigations_off();
}