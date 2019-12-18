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
 int EINVAL ; 
 int /*<<< orphan*/  SCTLR_EL1_SED ; 
 int /*<<< orphan*/  cpu_supports_mixed_endian_el0 () ; 
 int /*<<< orphan*/  sctlr_el1 ; 
 int /*<<< orphan*/  sysreg_clear_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setend_set_hw_mode(bool enable)
{
	if (!cpu_supports_mixed_endian_el0())
		return -EINVAL;

	if (enable)
		sysreg_clear_set(sctlr_el1, SCTLR_EL1_SED, 0);
	else
		sysreg_clear_set(sctlr_el1, 0, SCTLR_EL1_SED);
	return 0;
}