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
struct TYPE_3__ {scalar_t__ enabled; } ;
struct mpt_softc {scalar_t__ twildcard; scalar_t__ tenabled; scalar_t__ is_fc; TYPE_2__* trt; TYPE_1__ trt_wildcard; } ;
typedef  size_t lun_id_t ;
struct TYPE_4__ {scalar_t__ enabled; } ;

/* Variables and functions */
 size_t CAM_LUN_WILDCARD ; 
 scalar_t__ CAM_TARGET_WILDCARD ; 
 int EINVAL ; 
 size_t MPT_MAX_LUNS ; 
 int /*<<< orphan*/  mpt_fc_reset_link (struct mpt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_disable_lun(struct mpt_softc *mpt, target_id_t tgt, lun_id_t lun)
{
	int i;

	if (tgt == CAM_TARGET_WILDCARD && lun == CAM_LUN_WILDCARD) {
		mpt->twildcard = 0;
	} else if (lun >= MPT_MAX_LUNS) {
		return (EINVAL);
	} else if (tgt != CAM_TARGET_WILDCARD && tgt != 0) {
		return (EINVAL);
	}
	if (lun == CAM_LUN_WILDCARD) {
		mpt->trt_wildcard.enabled = 0;
	} else {
		mpt->trt[lun].enabled = 0;
	}
	for (i = 0; i < MPT_MAX_LUNS; i++) {
		if (mpt->trt[i].enabled) {
			break;
		}
	}
	if (i == MPT_MAX_LUNS && mpt->twildcard == 0) {
		if (mpt->is_fc) {
			(void) mpt_fc_reset_link(mpt, 0);
		}
		mpt->tenabled = 0;
	}
	return (0);
}