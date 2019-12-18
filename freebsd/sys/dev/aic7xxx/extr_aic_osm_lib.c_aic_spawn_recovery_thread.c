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
struct aic_softc {int /*<<< orphan*/  unit; TYPE_1__* platform_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  recovery_thread; } ;

/* Variables and functions */
 int aic_kthread_create (int /*<<< orphan*/ ,struct aic_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_recovery_thread ; 

int
aic_spawn_recovery_thread(struct aic_softc *aic)
{
	int error;

	error = aic_kthread_create(aic_recovery_thread, aic,
			       &aic->platform_data->recovery_thread,
			       /*flags*/0, /*altstack*/0, "aic_recovery%d",
			       aic->unit);
	return (error);
}