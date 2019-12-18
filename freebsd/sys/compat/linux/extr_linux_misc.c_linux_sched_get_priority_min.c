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
struct thread {int dummy; } ;
struct sched_get_priority_min_args {int /*<<< orphan*/  policy; } ;
struct linux_sched_get_priority_min_args {int policy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_SCHED_FIFO 130 
#define  LINUX_SCHED_OTHER 129 
#define  LINUX_SCHED_RR 128 
 int /*<<< orphan*/  SCHED_FIFO ; 
 int /*<<< orphan*/  SCHED_OTHER ; 
 int /*<<< orphan*/  SCHED_RR ; 
 int sys_sched_get_priority_min (struct thread*,struct sched_get_priority_min_args*) ; 

int
linux_sched_get_priority_min(struct thread *td,
    struct linux_sched_get_priority_min_args *args)
{
	struct sched_get_priority_min_args bsd;

	switch (args->policy) {
	case LINUX_SCHED_OTHER:
		bsd.policy = SCHED_OTHER;
		break;
	case LINUX_SCHED_FIFO:
		bsd.policy = SCHED_FIFO;
		break;
	case LINUX_SCHED_RR:
		bsd.policy = SCHED_RR;
		break;
	default:
		return (EINVAL);
	}
	return (sys_sched_get_priority_min(td, &bsd));
}