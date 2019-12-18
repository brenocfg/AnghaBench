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
typedef  scalar_t__ ypxfrstat ;
struct jobs {unsigned long tid; int polled; int /*<<< orphan*/  prognum; int /*<<< orphan*/  server; int /*<<< orphan*/  map; struct jobs* next; } ;

/* Variables and functions */
 scalar_t__ YPXFR_AGE ; 
 scalar_t__ YPXFR_SUCC ; 
 int /*<<< orphan*/  svc_unregister (int /*<<< orphan*/ ,int) ; 
 int verbose ; 
 int /*<<< orphan*/  yp_error (char*,unsigned long,...) ; 
 struct jobs* yppush_joblist ; 
 int /*<<< orphan*/  yppush_running_jobs ; 
 unsigned long yppusherr_string (scalar_t__) ; 
 unsigned long ypxfrerr_string (scalar_t__) ; 

__attribute__((used)) static int
yppush_show_status(ypxfrstat status, unsigned long tid)
{
	struct jobs *job;

	job = yppush_joblist;

	while (job != NULL) {
		if (job->tid == tid)
			break;
		job = job->next;
	}

	if (job == NULL) {
		yp_error("warning: received callback with invalid transaction ID: %lu",
			 tid);
		return (0);
	}

	if (job->polled) {
		yp_error("warning: received callback with duplicate transaction ID: %lu",
			 tid);
		return (0);
	}

	if (verbose > 1) {
		yp_error("checking return status: transaction ID: %lu",
								job->tid);
	}

	if (status != YPXFR_SUCC || verbose) {
		yp_error("transfer of map %s to server %s %s",
		 	job->map, job->server, status == YPXFR_SUCC ?
		 	"succeeded" : "failed");
		yp_error("status returned by ypxfr: %s", status > YPXFR_AGE ?
			yppusherr_string(status) :
			ypxfrerr_string(status));
	}

	job->polled = 1;

	svc_unregister(job->prognum, 1);

	yppush_running_jobs--;
	return(0);
}