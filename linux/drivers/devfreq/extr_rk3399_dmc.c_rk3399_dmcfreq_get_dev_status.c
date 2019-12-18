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
struct rk3399_dmcfreq {int /*<<< orphan*/  rate; int /*<<< orphan*/  edev; } ;
struct device {int dummy; } ;
struct devfreq_event_data {int /*<<< orphan*/  total_count; int /*<<< orphan*/  load_count; } ;
struct devfreq_dev_status {int /*<<< orphan*/  total_time; int /*<<< orphan*/  busy_time; int /*<<< orphan*/  current_frequency; } ;

/* Variables and functions */
 struct rk3399_dmcfreq* dev_get_drvdata (struct device*) ; 
 int devfreq_event_get_event (int /*<<< orphan*/ ,struct devfreq_event_data*) ; 

__attribute__((used)) static int rk3399_dmcfreq_get_dev_status(struct device *dev,
					 struct devfreq_dev_status *stat)
{
	struct rk3399_dmcfreq *dmcfreq = dev_get_drvdata(dev);
	struct devfreq_event_data edata;
	int ret = 0;

	ret = devfreq_event_get_event(dmcfreq->edev, &edata);
	if (ret < 0)
		return ret;

	stat->current_frequency = dmcfreq->rate;
	stat->busy_time = edata.load_count;
	stat->total_time = edata.total_count;

	return ret;
}