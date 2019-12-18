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
struct sched_param {int dummy; } ;

/* Variables and functions */
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int /*<<< orphan*/  quit (char*) ; 
 scalar_t__ sched_getparam (int /*<<< orphan*/ ,struct sched_param*) ; 
 int sched_getscheduler (int /*<<< orphan*/ ) ; 
 char* sched_text (int) ; 
 int /*<<< orphan*/  stderr ; 

int sched_is(int line, struct sched_param *p, int shouldbe)
{
	int scheduler;
	struct sched_param param;

	/* What scheduler are we running now?
	 */
	errno = 0;
	scheduler = sched_getscheduler(0);
	if (sched_getparam(0, &param))
		quit("sched_getparam");

	if (p)
		*p = param;

	if (shouldbe != -1 && scheduler != shouldbe)
	{
		fprintf(stderr,
		"At line %d the scheduler should be %s yet it is %s.\n",
		line, sched_text(shouldbe), sched_text(scheduler));

		exit(-1);
	}

	return scheduler;
}