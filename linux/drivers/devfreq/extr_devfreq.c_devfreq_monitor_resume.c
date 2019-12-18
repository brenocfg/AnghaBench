#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct devfreq {int stop_polling; unsigned long previous_freq; int /*<<< orphan*/  lock; TYPE_2__ dev; TYPE_1__* profile; int /*<<< orphan*/  last_stat_updated; int /*<<< orphan*/  work; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* get_cur_freq ) (int /*<<< orphan*/ ,unsigned long*) ;scalar_t__ polling_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devfreq_wq ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long*) ; 

void devfreq_monitor_resume(struct devfreq *devfreq)
{
	unsigned long freq;

	mutex_lock(&devfreq->lock);
	if (!devfreq->stop_polling)
		goto out;

	if (!delayed_work_pending(&devfreq->work) &&
			devfreq->profile->polling_ms)
		queue_delayed_work(devfreq_wq, &devfreq->work,
			msecs_to_jiffies(devfreq->profile->polling_ms));

	devfreq->last_stat_updated = jiffies;
	devfreq->stop_polling = false;

	if (devfreq->profile->get_cur_freq &&
		!devfreq->profile->get_cur_freq(devfreq->dev.parent, &freq))
		devfreq->previous_freq = freq;

out:
	mutex_unlock(&devfreq->lock);
}