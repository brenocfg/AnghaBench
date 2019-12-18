#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/ * filter_def; } ;
struct TYPE_5__ {int /*<<< orphan*/  os; TYPE_1__ config; void* hw_war_version; } ;
typedef  TYPE_2__ ocs_hw_t ;
typedef  int /*<<< orphan*/  ocs_hw_rtn_e ;
typedef  int ocs_hw_property_e ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
#define  OCS_HW_FILTER_DEF 129 
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
#define  OCS_HW_WAR_VERSION 128 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,int) ; 
 char* ocs_strchr (char*,char) ; 
 int /*<<< orphan*/  ocs_strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ocs_hw_rtn_e
ocs_hw_set_ptr(ocs_hw_t *hw, ocs_hw_property_e prop, void *value)
{
	ocs_hw_rtn_e rc = OCS_HW_RTN_SUCCESS;

	switch (prop) {
	case OCS_HW_WAR_VERSION:
		hw->hw_war_version = value;
		break;
	case OCS_HW_FILTER_DEF: {
		char *p = value;
		uint32_t idx = 0;

		for (idx = 0; idx < ARRAY_SIZE(hw->config.filter_def); idx++) {
			hw->config.filter_def[idx] = 0;
		}

		for (idx = 0; (idx < ARRAY_SIZE(hw->config.filter_def)) && (p != NULL) && *p; ) {
			hw->config.filter_def[idx++] = ocs_strtoul(p, 0, 0);
			p = ocs_strchr(p, ',');
			if (p != NULL) {
				p++;
			}
		}

		break;
	}
	default:
		ocs_log_test(hw->os, "unsupported property %#x\n", prop);
		rc = OCS_HW_RTN_ERROR;
		break;
	}
	return rc;
}