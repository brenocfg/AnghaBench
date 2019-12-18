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
struct devfreq {int dummy; } ;

/* Variables and functions */
#define  DEVFREQ_GOV_INTERVAL 132 
#define  DEVFREQ_GOV_RESUME 131 
#define  DEVFREQ_GOV_START 130 
#define  DEVFREQ_GOV_STOP 129 
#define  DEVFREQ_GOV_SUSPEND 128 
 int /*<<< orphan*/  devfreq_interval_update (struct devfreq*,unsigned int*) ; 
 int /*<<< orphan*/  devfreq_monitor_resume (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_start (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_stop (struct devfreq*) ; 
 int /*<<< orphan*/  devfreq_monitor_suspend (struct devfreq*) ; 

__attribute__((used)) static int devfreq_simple_ondemand_handler(struct devfreq *devfreq,
				unsigned int event, void *data)
{
	switch (event) {
	case DEVFREQ_GOV_START:
		devfreq_monitor_start(devfreq);
		break;

	case DEVFREQ_GOV_STOP:
		devfreq_monitor_stop(devfreq);
		break;

	case DEVFREQ_GOV_INTERVAL:
		devfreq_interval_update(devfreq, (unsigned int *)data);
		break;

	case DEVFREQ_GOV_SUSPEND:
		devfreq_monitor_suspend(devfreq);
		break;

	case DEVFREQ_GOV_RESUME:
		devfreq_monitor_resume(devfreq);
		break;

	default:
		break;
	}

	return 0;
}