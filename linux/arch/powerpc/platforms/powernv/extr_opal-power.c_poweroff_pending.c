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
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int OPAL_SUCCESS ; 
 scalar_t__ detect_epow () ; 
 int opal_get_dpo_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static bool poweroff_pending(void)
{
	int rc;
	__be64 opal_dpo_timeout;

	/* Check for DPO event */
	rc = opal_get_dpo_status(&opal_dpo_timeout);
	if (rc == OPAL_SUCCESS) {
		pr_info("Existing DPO event detected.\n");
		return true;
	}

	/* Check for EPOW event */
	if (detect_epow()) {
		pr_info("Existing EPOW event detected.\n");
		return true;
	}

	return false;
}