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
 int /*<<< orphan*/  PSCI_0_2_FN_MIGRATE_INFO_TYPE ; 
 int invoke_psci_fn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int psci_migrate_info_type(void)
{
	return invoke_psci_fn(PSCI_0_2_FN_MIGRATE_INFO_TYPE, 0, 0, 0);
}