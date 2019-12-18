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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SMCCC_ARCH_WORKAROUND_1 ; 
 scalar_t__ SMCCC_VERSION_1_0 ; 
 int psci_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ smccc_version ; 

int
smccc_arch_workaround_1(void)
{

	KASSERT(smccc_version != SMCCC_VERSION_1_0,
	    ("SMCCC arch workaround 1 called with an invalid SMCCC interface"));
	return (psci_call(SMCCC_ARCH_WORKAROUND_1, 0, 0, 0));
}