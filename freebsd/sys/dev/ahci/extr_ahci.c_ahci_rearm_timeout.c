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
struct ahci_slot {scalar_t__ state; TYPE_2__* ccb; int /*<<< orphan*/  timeout; } ;
struct ahci_channel {int numslots; int toslots; struct ahci_slot* slot; int /*<<< orphan*/  mtx; } ;
struct TYPE_3__ {int timeout; } ;
struct TYPE_4__ {TYPE_1__ ccb_h; } ;

/* Variables and functions */
 scalar_t__ AHCI_SLOT_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SBT_1MS ; 
 scalar_t__ ahci_timeout ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ahci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_rearm_timeout(struct ahci_channel *ch)
{
	int i;

	mtx_assert(&ch->mtx, MA_OWNED);
	for (i = 0; i < ch->numslots; i++) {
		struct ahci_slot *slot = &ch->slot[i];

		/* Do we have a running request on slot? */
		if (slot->state < AHCI_SLOT_RUNNING)
			continue;
		if ((ch->toslots & (1 << i)) == 0)
			continue;
		callout_reset_sbt(&slot->timeout,
    	    	    SBT_1MS * slot->ccb->ccb_h.timeout / 2, 0,
		    (timeout_t*)ahci_timeout, slot, 0);
	}
}