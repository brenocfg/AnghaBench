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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  PSCI_RETVAL_NOT_SUPPORTED ; 
 int /*<<< orphan*/  SMCCC_ARCH_FEATURES ; 
 scalar_t__ SMCCC_VERSION_1_0 ; 
 int /*<<< orphan*/  psci_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smccc_version ; 

int32_t
smccc_arch_features(uint32_t smccc_func_id)
{

	if (smccc_version == SMCCC_VERSION_1_0)
		return (PSCI_RETVAL_NOT_SUPPORTED);

	return (psci_call(SMCCC_ARCH_FEATURES, smccc_func_id, 0, 0));
}