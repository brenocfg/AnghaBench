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
 int /*<<< orphan*/  PCPU_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMCCC_ARCH_WORKAROUND_1 ; 
 scalar_t__ SMCCC_RET_SUCCESS ; 
 int /*<<< orphan*/  bp_harden ; 
 scalar_t__ smccc_arch_features (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smccc_arch_workaround_1 ; 

__attribute__((used)) static void
install_psci_bp_hardening(void)
{

	if (smccc_arch_features(SMCCC_ARCH_WORKAROUND_1) != SMCCC_RET_SUCCESS)
		return;

	PCPU_SET(bp_harden, smccc_arch_workaround_1);
}