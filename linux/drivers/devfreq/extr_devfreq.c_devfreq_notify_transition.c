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
struct devfreq_freqs {int dummy; } ;
struct devfreq {int /*<<< orphan*/  transition_notifier_list; } ;

/* Variables and functions */
#define  DEVFREQ_POSTCHANGE 129 
#define  DEVFREQ_PRECHANGE 128 
 int EINVAL ; 
 int /*<<< orphan*/  srcu_notifier_call_chain (int /*<<< orphan*/ *,int const,struct devfreq_freqs*) ; 

__attribute__((used)) static int devfreq_notify_transition(struct devfreq *devfreq,
		struct devfreq_freqs *freqs, unsigned int state)
{
	if (!devfreq)
		return -EINVAL;

	switch (state) {
	case DEVFREQ_PRECHANGE:
		srcu_notifier_call_chain(&devfreq->transition_notifier_list,
				DEVFREQ_PRECHANGE, freqs);
		break;

	case DEVFREQ_POSTCHANGE:
		srcu_notifier_call_chain(&devfreq->transition_notifier_list,
				DEVFREQ_POSTCHANGE, freqs);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}