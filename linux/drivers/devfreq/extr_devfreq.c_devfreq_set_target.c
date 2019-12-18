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
typedef  int /*<<< orphan*/  u32 ;
struct devfreq_freqs {unsigned long old; unsigned long new; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct devfreq {unsigned long previous_freq; unsigned long resume_freq; scalar_t__ suspend_freq; TYPE_2__ dev; TYPE_1__* profile; } ;
struct TYPE_3__ {int (* target ) (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_cur_freq ) (int /*<<< orphan*/ ,unsigned long*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFREQ_POSTCHANGE ; 
 int /*<<< orphan*/  DEVFREQ_PRECHANGE ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devfreq_notify_transition (struct devfreq*,struct devfreq_freqs*,int /*<<< orphan*/ ) ; 
 scalar_t__ devfreq_update_status (struct devfreq*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,unsigned long*) ; 
 int stub2 (int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int devfreq_set_target(struct devfreq *devfreq, unsigned long new_freq,
			      u32 flags)
{
	struct devfreq_freqs freqs;
	unsigned long cur_freq;
	int err = 0;

	if (devfreq->profile->get_cur_freq)
		devfreq->profile->get_cur_freq(devfreq->dev.parent, &cur_freq);
	else
		cur_freq = devfreq->previous_freq;

	freqs.old = cur_freq;
	freqs.new = new_freq;
	devfreq_notify_transition(devfreq, &freqs, DEVFREQ_PRECHANGE);

	err = devfreq->profile->target(devfreq->dev.parent, &new_freq, flags);
	if (err) {
		freqs.new = cur_freq;
		devfreq_notify_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);
		return err;
	}

	freqs.new = new_freq;
	devfreq_notify_transition(devfreq, &freqs, DEVFREQ_POSTCHANGE);

	if (devfreq_update_status(devfreq, new_freq))
		dev_err(&devfreq->dev,
			"Couldn't update frequency transition information.\n");

	devfreq->previous_freq = new_freq;

	if (devfreq->suspend_freq)
		devfreq->resume_freq = cur_freq;

	return err;
}