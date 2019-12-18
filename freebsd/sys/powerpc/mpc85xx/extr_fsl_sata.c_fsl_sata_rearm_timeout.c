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
typedef  int /*<<< orphan*/  timeout_t ;
struct fsl_sata_slot {scalar_t__ state; TYPE_2__* ccb; int /*<<< orphan*/  timeout; } ;
struct fsl_sata_channel {int toslots; struct fsl_sata_slot* slot; int /*<<< orphan*/  mtx; } ;
struct TYPE_3__ {int timeout; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int FSL_SATA_MAX_SLOTS ; 
 scalar_t__ FSL_SATA_SLOT_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fsl_sata_slot*,int /*<<< orphan*/ ) ; 
 scalar_t__ fsl_sata_timeout ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_sata_rearm_timeout(struct fsl_sata_channel *ch)
{
	int i;

	mtx_assert(&ch->mtx, MA_OWNED);
	for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
		struct fsl_sata_slot *slot = &ch->slot[i];

		/* Do we have a running request on slot? */
		if (slot->state < FSL_SATA_SLOT_RUNNING)
			continue;
		if ((ch->toslots & (1 << i)) == 0)
			continue;
		callout_reset_sbt(&slot->timeout,
 	    	    SBT_1MS * slot->ccb->ccb_h.timeout / 2, 0,
		    (timeout_t*)fsl_sata_timeout, slot, 0);
	}
}