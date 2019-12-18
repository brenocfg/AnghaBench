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
struct aic_softc {TYPE_1__* platform_data; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * recovery_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC_SHUTDOWN_RECOVERY ; 
 int /*<<< orphan*/  PUSER ; 
 int /*<<< orphan*/  msleep (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct aic_softc*) ; 

void
aic_terminate_recovery_thread(struct aic_softc *aic)
{

	if (aic->platform_data->recovery_thread == NULL) {
		return;
	}
	aic->flags |= AIC_SHUTDOWN_RECOVERY;
	wakeup(aic);
	/*
	 * Sleep on a slightly different location 
	 * for this interlock just for added safety.
	 */
	msleep(aic->platform_data, &aic->platform_data->mtx, PUSER, "thtrm", 0);
}