#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ target_id_t ;
struct ccb_hdr {scalar_t__ target_id; size_t target_lun; } ;
typedef  int /*<<< orphan*/  ocs_tgt_resource_t ;
struct TYPE_3__ {int /*<<< orphan*/ * targ_rsrc; int /*<<< orphan*/  targ_rsrc_wildcard; } ;
typedef  TYPE_1__ ocs_fcport ;
typedef  size_t lun_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_LUN_INVALID ; 
 size_t CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 
 size_t OCS_MAX_LUN ; 

__attribute__((used)) static ocs_tgt_resource_t *ocs_tgt_resource_get(ocs_fcport *fcp, 
				struct ccb_hdr *ccb_h, uint32_t *status)
{
	target_id_t	tid = ccb_h->target_id;
	lun_id_t	lun = ccb_h->target_lun;

	if (CAM_TARGET_WILDCARD == tid) {
		if (CAM_LUN_WILDCARD != lun) {
			*status = CAM_LUN_INVALID;
			return NULL;
		}
		return &fcp->targ_rsrc_wildcard;
	} else {
		if (lun < OCS_MAX_LUN) {
			return &fcp->targ_rsrc[lun];
		} else {
			*status = CAM_LUN_INVALID;
			return NULL;
		}
	} 

}