#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ sli4_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SLI4_IF_TYPE_BE3_SKH_PF ; 
 int SLI4_PORT_STATUS_RN ; 
 int /*<<< orphan*/  SLI4_REG_SLIPORT_STATUS ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sli_get_if_type (TYPE_1__*) ; 
 int sli_reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

int32_t sli_reset_required(sli4_t *sli4)
{
	uint32_t val;

	if (SLI4_IF_TYPE_BE3_SKH_PF == sli_get_if_type(sli4)) {
		ocs_log_test(sli4->os, "reset required N/A for iftype 0\n");
		return 0;
	}

	val = sli_reg_read(sli4, SLI4_REG_SLIPORT_STATUS);
	if (UINT32_MAX == val) {
		ocs_log_err(sli4->os, "error reading SLIPORT_STATUS\n");
		return -1;
	} else {
		return ((val & SLI4_PORT_STATUS_RN) ? 1 : 0);
	}
}