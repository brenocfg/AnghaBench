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
struct ha_softc {int ha_shutdown; int ha_wakeup; int /*<<< orphan*/  ha_lock; } ;
struct ctl_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHEDULER_STOPPED () ; 
 struct ha_softc ha_softc ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
ctl_ha_msg_shutdown(struct ctl_softc *ctl_softc)
{
	struct ha_softc *softc = &ha_softc;

	/* Disconnect and shutdown threads. */
	mtx_lock(&softc->ha_lock);
	if (softc->ha_shutdown < 2) {
		softc->ha_shutdown = 1;
		softc->ha_wakeup = 1;
		wakeup(&softc->ha_wakeup);
		while (softc->ha_shutdown < 2 && !SCHEDULER_STOPPED()) {
			msleep(&softc->ha_wakeup, &softc->ha_lock, 0,
			    "shutdown", hz);
		}
	}
	mtx_unlock(&softc->ha_lock);
}