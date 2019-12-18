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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ PSCI_RETVAL_NOT_SUPPORTED ; 
 int /*<<< orphan*/  SMCCC_VERSION ; 
 int SMCCC_VERSION_MAJOR (scalar_t__) ; 
 int SMCCC_VERSION_MINOR (scalar_t__) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 scalar_t__ psci_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ psci_features (int /*<<< orphan*/ ) ; 
 scalar_t__ smccc_version ; 

__attribute__((used)) static void
smccc_init(void *dummy)
{
	int32_t features;
	uint32_t ret;

	features = psci_features(SMCCC_VERSION);
	if (features != PSCI_RETVAL_NOT_SUPPORTED) {
		ret = psci_call(SMCCC_VERSION, 0, 0, 0);
		/* This should always be the case as we checked it above */
		if (ret > 0)
			smccc_version = ret;
	}

	if (bootverbose) {
		printf("Found SMCCC version %u.%u\n",
		    SMCCC_VERSION_MAJOR(smccc_version),
		    SMCCC_VERSION_MINOR(smccc_version));
	}
}