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
struct aic_softc {int flags; TYPE_1__* platform_data; int /*<<< orphan*/  timedout_scbs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * recovery_thread; int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int AIC_SHUTDOWN_RECOVERY ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  aic_lock (struct aic_softc*) ; 
 int /*<<< orphan*/  aic_recover_commands (struct aic_softc*) ; 
 int /*<<< orphan*/  aic_unlock (struct aic_softc*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct aic_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static void
aic_recovery_thread(void *arg)
{
	struct aic_softc *aic;

	aic = (struct aic_softc *)arg;
	aic_lock(aic);
	for (;;) {
		
		if (LIST_EMPTY(&aic->timedout_scbs) != 0
		 && (aic->flags & AIC_SHUTDOWN_RECOVERY) == 0)
			msleep(aic, &aic->platform_data->mtx, PUSER, "idle", 0);

		if ((aic->flags & AIC_SHUTDOWN_RECOVERY) != 0)
			break;

		aic_recover_commands(aic);
	}
	aic->platform_data->recovery_thread = NULL;
	wakeup(aic->platform_data);
	aic_unlock(aic);
	kproc_exit(0);
}