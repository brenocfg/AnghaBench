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
struct jobs {scalar_t__ polled; int server; char* tid; struct jobs* next; int /*<<< orphan*/  prognum; } ;

/* Variables and functions */
 int /*<<< orphan*/  YPPUSH_RESPONSE_TIMEOUT ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_unregister (int /*<<< orphan*/ ,int) ; 
 int verbose ; 
 int /*<<< orphan*/  yp_error (char*,...) ; 
 struct jobs* yppush_joblist ; 
 scalar_t__ yppush_svc_run (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
yppush_exit(int now)
{
	struct jobs *jptr;
	int still_pending = 1;

	/* Let all the information trickle in. */
	while (!now && still_pending) {
		jptr = yppush_joblist;
		still_pending = 0;
		while (jptr) {
			if (jptr->polled == 0) {
				still_pending++;
				if (verbose > 1)
					yp_error("%s has not responded",
						  jptr->server);
			} else {
				if (verbose > 1)
					yp_error("%s has responded",
						  jptr->server);
			}
			jptr = jptr->next;
		}
		if (still_pending) {
			if (verbose > 1)
				yp_error("%d transfer%sstill pending",
					still_pending,
					still_pending > 1 ? "s " : " ");
			if (yppush_svc_run (YPPUSH_RESPONSE_TIMEOUT) == 0) {
				yp_error("timed out");
				now = 1;
			}
		} else {
			if (verbose)
				yp_error("all transfers complete");
			break;
		}
	}


	/* All stats collected and reported -- kill all the stragglers. */
	jptr = yppush_joblist;
	while (jptr) {
		if (!jptr->polled)
			yp_error("warning: exiting with transfer \
to %s (transid = %lu) still pending", jptr->server, jptr->tid);
		svc_unregister(jptr->prognum, 1);
		jptr = jptr->next;
	}

	exit(0);
}