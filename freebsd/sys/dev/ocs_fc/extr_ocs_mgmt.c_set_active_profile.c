#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ ocs_t ;
struct TYPE_8__ {scalar_t__ status; int /*<<< orphan*/  semaphore; } ;
typedef  TYPE_2__ ocs_mgmt_set_active_profile_result_t ;
typedef  int int32_t ;

/* Variables and functions */
 int ENXIO ; 
 int OCS_HW_RTN_SUCCESS ; 
 int /*<<< orphan*/  OCS_SEM_FOREVER ; 
 int ocs_hw_set_active_profile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_test (TYPE_1__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ocs_mgmt_set_active_profile_cb ; 
 int /*<<< orphan*/  ocs_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ocs_sem_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ocs_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int32_t
set_active_profile(ocs_t *ocs, char *name, char *value)
{
	ocs_mgmt_set_active_profile_result_t result;
	int32_t rc = 0;
	int32_t new_profile;

	new_profile = ocs_strtoul(value, NULL, 0);

	ocs_sem_init(&(result.semaphore), 0, "set_active_profile");

	rc = ocs_hw_set_active_profile(&ocs->hw, ocs_mgmt_set_active_profile_cb, new_profile, &result);
	if (rc == OCS_HW_RTN_SUCCESS) {
		if (ocs_sem_p(&(result.semaphore), OCS_SEM_FOREVER) != 0) {
			/* Undefined failure */
			ocs_log_err(ocs, "ocs_sem_p failed\n");
			return -ENXIO;
		}
		if (result.status == 0) {
			/* Success. */
			rc = 0;
		} else {
			rc = -1;
			ocs_log_test(ocs, "setting active profile status 0x%x\n", result.status);
		}
	}

	return rc;
}