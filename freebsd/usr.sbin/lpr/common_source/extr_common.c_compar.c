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
struct jobqueue {scalar_t__ job_time; char* job_cfname; } ;

/* Variables and functions */
 int strcmp (char*,char*) ; 

__attribute__((used)) static int
compar(const void *p1, const void *p2)
{
	const struct jobqueue *qe1, *qe2;

	qe1 = *(const struct jobqueue * const *)p1;
	qe2 = *(const struct jobqueue * const *)p2;
	
	if (qe1->job_time < qe2->job_time)
		return (-1);
	if (qe1->job_time > qe2->job_time)
		return (1);
	/*
	 * At this point, the two files have the same last-modification time.
	 * return a result based on filenames, so that 'cfA001some.host' will
	 * come before 'cfA002some.host'.  Since the jobid ('001') will wrap
	 * around when it gets to '999', we also assume that '9xx' jobs are
	 * older than '0xx' jobs.
	*/
	if ((qe1->job_cfname[3] == '9') && (qe2->job_cfname[3] == '0'))
		return (-1);
	if ((qe1->job_cfname[3] == '0') && (qe2->job_cfname[3] == '9'))
		return (1);
	return (strcmp(qe1->job_cfname, qe2->job_cfname));
}