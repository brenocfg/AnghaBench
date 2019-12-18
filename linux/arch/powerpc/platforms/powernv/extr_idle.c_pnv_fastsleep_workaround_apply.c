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
 int /*<<< orphan*/  OPAL_CONFIG_IDLE_APPLY ; 
 int /*<<< orphan*/  OPAL_CONFIG_IDLE_FASTSLEEP ; 
 int opal_config_cpu_idle_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pnv_fastsleep_workaround_apply(void *info)

{
	int rc;
	int *err = info;

	rc = opal_config_cpu_idle_state(OPAL_CONFIG_IDLE_FASTSLEEP,
					OPAL_CONFIG_IDLE_APPLY);
	if (rc)
		*err = 1;
}