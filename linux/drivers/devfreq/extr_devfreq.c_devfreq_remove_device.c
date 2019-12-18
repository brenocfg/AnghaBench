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
struct devfreq {int /*<<< orphan*/  dev; TYPE_1__* governor; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_GOV_STOP ; 
 int EINVAL ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct devfreq*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int devfreq_remove_device(struct devfreq *devfreq)
{
	if (!devfreq)
		return -EINVAL;

	if (devfreq->governor)
		devfreq->governor->event_handler(devfreq,
						 DEVFREQ_GOV_STOP, NULL);
	device_unregister(&devfreq->dev);

	return 0;
}