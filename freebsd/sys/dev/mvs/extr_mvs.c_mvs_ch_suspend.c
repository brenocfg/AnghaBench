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
struct mvs_channel {int /*<<< orphan*/  mtx; int /*<<< orphan*/  sim; int /*<<< orphan*/  reset_timer; scalar_t__ resetting; scalar_t__ oslots; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  msleep (struct mvs_channel*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvs_ch_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_freeze_simq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xpt_release_simq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mvs_ch_suspend(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);

	mtx_lock(&ch->mtx);
	xpt_freeze_simq(ch->sim, 1);
	while (ch->oslots)
		msleep(ch, &ch->mtx, PRIBIO, "mvssusp", hz/100);
	/* Forget about reset. */
	if (ch->resetting) {
		ch->resetting = 0;
		callout_stop(&ch->reset_timer);
		xpt_release_simq(ch->sim, TRUE);
	}
	mvs_ch_deinit(dev);
	mtx_unlock(&ch->mtx);
	return (0);
}