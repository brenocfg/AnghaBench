#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ahci_channel {int resetting; int /*<<< orphan*/  reset_timer; int /*<<< orphan*/  sim; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ahci_clo (struct ahci_channel*) ; 
 int /*<<< orphan*/  ahci_start (struct ahci_channel*,int) ; 
 scalar_t__ ahci_wait_ready (struct ahci_channel*,int,int) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int hz ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahci_reset_to(void *arg)
{
	struct ahci_channel *ch = arg;

	if (ch->resetting == 0)
		return;
	ch->resetting--;
	if (ahci_wait_ready(ch, ch->resetting == 0 ? -1 : 0,
	    (310 - ch->resetting) * 100) == 0) {
		ch->resetting = 0;
		ahci_start(ch, 1);
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	if (ch->resetting == 0) {
		ahci_clo(ch);
		ahci_start(ch, 1);
		xpt_release_simq(ch->sim, TRUE);
		return;
	}
	callout_schedule(&ch->reset_timer, hz / 10);
}