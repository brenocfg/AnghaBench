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
struct tegra_devfreq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct devfreq {TYPE_1__ dev; } ;

/* Variables and functions */
#define  DEVFREQ_GOV_RESUME 131 
#define  DEVFREQ_GOV_START 130 
#define  DEVFREQ_GOV_STOP 129 
#define  DEVFREQ_GOV_SUSPEND 128 
 struct tegra_devfreq* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devfreq_monitor_resume (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_start (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_stop (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_suspend (struct devfreq*) ; 
 int /*<<< orphan*/  tegra_actmon_start (struct tegra_devfreq*) ; 
 int /*<<< orphan*/  tegra_actmon_stop (struct tegra_devfreq*) ; 

__attribute__((used)) static int tegra_governor_event_handler(struct devfreq *devfreq,
					unsigned int event, void *data)
{
	struct tegra_devfreq *tegra = dev_get_drvdata(devfreq->dev.parent);

	switch (event) {
	case DEVFREQ_GOV_START:
		devfreq_monitor_start(devfreq);
		tegra_actmon_start(tegra);
		break;

	case DEVFREQ_GOV_STOP:
		tegra_actmon_stop(tegra);
		devfreq_monitor_stop(devfreq);
		break;

	case DEVFREQ_GOV_SUSPEND:
		tegra_actmon_stop(tegra);
		devfreq_monitor_suspend(devfreq);
		break;

	case DEVFREQ_GOV_RESUME:
		devfreq_monitor_resume(devfreq);
		tegra_actmon_start(tegra);
		break;
	}

	return 0;
}