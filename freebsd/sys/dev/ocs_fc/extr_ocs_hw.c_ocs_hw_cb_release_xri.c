#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int released_xri_count; TYPE_1__* xri_tbl; } ;
typedef  TYPE_2__ sli4_cmd_release_xri_t ;
struct TYPE_8__ {int /*<<< orphan*/  os; } ;
typedef  TYPE_3__ ocs_hw_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  xri_tag1; int /*<<< orphan*/  xri_tag0; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLI4_BMBX_SIZE ; 
 int /*<<< orphan*/  ocs_free (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_hw_reclaim_xri (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_log_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int32_t
ocs_hw_cb_release_xri(ocs_hw_t *hw, int32_t status, uint8_t *mqe, void  *arg)
{
	sli4_cmd_release_xri_t	*release_xri = (sli4_cmd_release_xri_t*)mqe;
	uint8_t i;

	/* Reclaim the XRIs as host owned if the command fails */
	if (status != 0) {
		ocs_log_err(hw->os, "Status 0x%x\n", status);
	} else {
		for (i = 0; i < release_xri->released_xri_count; i++) {
			uint16_t xri = ((i & 1) == 0 ? release_xri->xri_tbl[i/2].xri_tag0 :
					release_xri->xri_tbl[i/2].xri_tag1);
			ocs_hw_reclaim_xri(hw, xri, 1);
		}
	}

	ocs_free(hw->os, mqe, SLI4_BMBX_SIZE);
	return 0;
}