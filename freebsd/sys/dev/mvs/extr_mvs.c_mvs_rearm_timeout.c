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
struct mvs_slot {scalar_t__ state; TYPE_2__* ccb; int /*<<< orphan*/  timeout; } ;
struct mvs_channel {int toslots; struct mvs_slot* slot; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int timeout; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MVS_MAX_SLOTS ; 
 scalar_t__ MVS_SLOT_RUNNING ; 
 int SBT_1MS ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mvs_slot*,int /*<<< orphan*/ ) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ mvs_timeout ; 

__attribute__((used)) static void
mvs_rearm_timeout(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	int i;

	mtx_assert(&ch->mtx, MA_OWNED);
	for (i = 0; i < MVS_MAX_SLOTS; i++) {
		struct mvs_slot *slot = &ch->slot[i];

		/* Do we have a running request on slot? */
		if (slot->state < MVS_SLOT_RUNNING)
			continue;
		if ((ch->toslots & (1 << i)) == 0)
			continue;
		callout_reset_sbt(&slot->timeout,
		    SBT_1MS * slot->ccb->ccb_h.timeout / 2, 0,
		    (timeout_t*)mvs_timeout, slot, 0);
	}
}