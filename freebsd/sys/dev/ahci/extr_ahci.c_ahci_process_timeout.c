#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ahci_channel {int numslots; TYPE_1__* slot; int /*<<< orphan*/  mtx; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHCI_ERR_TIMEOUT ; 
 scalar_t__ AHCI_SLOT_RUNNING ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  ahci_end_transaction (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_process_timeout(struct ahci_channel *ch)
{
	int i;

	mtx_assert(&ch->mtx, MA_OWNED);
	/* Handle the rest of commands. */
	for (i = 0; i < ch->numslots; i++) {
		/* Do we have a running request on slot? */
		if (ch->slot[i].state < AHCI_SLOT_RUNNING)
			continue;
		ahci_end_transaction(&ch->slot[i], AHCI_ERR_TIMEOUT);
	}
}