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
struct sched_param {int sched_priority; } ;
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRIO_PROCESS ; 
 int /*<<< orphan*/  SCHED_RR ; 
 int /*<<< orphan*/  WWW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct sched_param*,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ pthread_setaffinity_np (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ sched_setscheduler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sched_param*) ; 
 scalar_t__ setpriority (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
setaffinity(int i)
{
        cpuset_t cpumask;
	struct sched_param p;

        if (i == -1)
                return 0;

        /* Set thread affinity affinity.*/
        CPU_ZERO(&cpumask);
        CPU_SET(i, &cpumask);

        if (pthread_setaffinity_np(pthread_self(), sizeof(cpuset_t), &cpumask) != 0) {
                WWW("Unable to set affinity: %s", strerror(errno));
        }
	if (setpriority(PRIO_PROCESS, 0, -10)) {; // XXX not meaningful
                WWW("Unable to set priority: %s", strerror(errno));
	}
	bzero(&p, sizeof(p));
	p.sched_priority = 10; // 99 on linux ?
	// use SCHED_RR or SCHED_FIFO
	if (sched_setscheduler(0, SCHED_RR, &p)) {
                WWW("Unable to set scheduler: %s", strerror(errno));
	}
        return 0;
}