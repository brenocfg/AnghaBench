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
struct mvs_intr_arg {int cause; int /*<<< orphan*/  arg; } ;
struct mvs_channel {scalar_t__ resetting; scalar_t__ resetpolldiv; int /*<<< orphan*/  dev; int /*<<< orphan*/  reset_timer; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ cam_sim_softc (struct cam_sim*) ; 
 int /*<<< orphan*/  mvs_ch_intr (struct mvs_intr_arg*) ; 
 int /*<<< orphan*/  mvs_reset_to (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvspoll(struct cam_sim *sim)
{
	struct mvs_channel *ch = (struct mvs_channel *)cam_sim_softc(sim);
	struct mvs_intr_arg arg;

	arg.arg = ch->dev;
	arg.cause = 2 | 4; /* XXX */
	mvs_ch_intr(&arg);
	if (ch->resetting != 0 &&
	    (--ch->resetpolldiv <= 0 || !callout_pending(&ch->reset_timer))) {
		ch->resetpolldiv = 1000;
		mvs_reset_to(ch->dev);
	}
}