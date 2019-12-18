#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_9__ {scalar_t__ override_fcfi; } ;
struct TYPE_10__ {size_t first_domain_idx; size_t* fcf_index_fcfi; int /*<<< orphan*/  os; TYPE_1__ workaround; TYPE_3__** domains; } ;
typedef  TYPE_2__ ocs_hw_t ;
struct TYPE_11__ {size_t fcf_indicator; size_t fcf; } ;
typedef  TYPE_3__ ocs_domain_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_RTN_ERROR ; 
 int /*<<< orphan*/  OCS_HW_RTN_SUCCESS ; 
 size_t SLI4_MAX_FCFI ; 
 size_t SLI4_MAX_FCF_INDEX ; 
 size_t UINT16_MAX ; 
 int /*<<< orphan*/  ocs_log_debug (int /*<<< orphan*/ ,char*,TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ *,char*,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_log_test (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int32_t
ocs_hw_domain_del(ocs_hw_t *hw, ocs_domain_t *domain)
{
	int32_t		rc = OCS_HW_RTN_ERROR;
	uint16_t	fcfi = UINT16_MAX;

	if ((hw == NULL) || (domain == NULL)) {
		ocs_log_err(NULL, "bad parameter hw=%p domain=%p\n",
				hw, domain);
		return OCS_HW_RTN_ERROR;
	}

	fcfi = domain->fcf_indicator;

	if (fcfi < SLI4_MAX_FCFI) {
		uint16_t	fcf_index = UINT16_MAX;

		ocs_log_debug(hw->os, "deleting domain %p @ %#x\n",
				domain, fcfi);

		if (domain != hw->domains[fcfi]) {
			ocs_log_test(hw->os, "provided domain %p does not match stored domain %p\n",
				     domain, hw->domains[fcfi]);
			return OCS_HW_RTN_ERROR;
		}

		hw->domains[fcfi] = NULL;

		/* HW_WORKAROUND_OVERRIDE_FCFI_IN_SRB */
		if (hw->workaround.override_fcfi) {
			if (hw->first_domain_idx == fcfi) {
				hw->first_domain_idx = -1;
			}
		}

		fcf_index = domain->fcf;

		if (fcf_index < SLI4_MAX_FCF_INDEX) {
			if (hw->fcf_index_fcfi[fcf_index] == fcfi) {
				hw->fcf_index_fcfi[fcf_index] = 0;
				rc = OCS_HW_RTN_SUCCESS;
			} else {
				ocs_log_test(hw->os, "indexed FCFI %#x doesn't match provided %#x @ %d\n",
					     hw->fcf_index_fcfi[fcf_index], fcfi, fcf_index);
			}
		} else {
			ocs_log_test(hw->os, "FCF index %d out of range (max %d)\n",
				     fcf_index, SLI4_MAX_FCF_INDEX);
		}
	} else {
		ocs_log_test(hw->os, "FCFI %#x out of range (max %#x)\n",
				fcfi, SLI4_MAX_FCFI);
	}

	return rc;
}