#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ target_id_t ;
struct TYPE_3__ {int enabled; } ;
struct mpt_softc {int twildcard; int tenabled; TYPE_2__* trt; TYPE_1__ trt_wildcard; scalar_t__ is_fc; } ;
typedef  size_t lun_id_t ;
struct TYPE_4__ {int enabled; } ;

/* Variables and functions */
 size_t CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 
 int EINVAL ; 
 size_t MPT_MAX_LUNS ; 
 int /*<<< orphan*/  mpt_fc_reset_link (struct mpt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_enable_lun(struct mpt_softc *mpt, target_id_t tgt, lun_id_t lun)
{

	if (tgt == CAM_TARGET_WILDCARD && lun == CAM_LUN_WILDCARD) {
		mpt->twildcard = 1;
	} else if (lun >= MPT_MAX_LUNS) {
		return (EINVAL);
	} else if (tgt != CAM_TARGET_WILDCARD && tgt != 0) {
		return (EINVAL);
	}
	if (mpt->tenabled == 0) {
		if (mpt->is_fc) {
			(void) mpt_fc_reset_link(mpt, 0);
		}
		mpt->tenabled = 1;
	}
	if (lun == CAM_LUN_WILDCARD) {
		mpt->trt_wildcard.enabled = 1;
	} else {
		mpt->trt[lun].enabled = 1;
	}
	return (0);
}