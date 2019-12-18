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

/* Variables and functions */
 int YP_TRUE ; 
 int /*<<< orphan*/  asprintf (char**,char*,int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ skip_master ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int yp_errno ; 
 scalar_t__ yp_push (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ yppush_jobs ; 
 int /*<<< orphan*/  yppush_mapname ; 
 int /*<<< orphan*/  yppush_master ; 
 scalar_t__ yppush_running_jobs ; 
 scalar_t__ yppush_svc_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yppush_timeout ; 
 int /*<<< orphan*/  yppush_transid ; 

__attribute__((used)) static int
yppush_foreach(int status, char *key, int keylen, char *val, int vallen,
    char *data)
{
	char *server;

	if (status != YP_TRUE)
		return (status);

	asprintf(&server, "%.*s", vallen, val);

	/*
	 * Do not stop the iteration on the allocation failure.  We
	 * cannot usefully react on low memory condition anyway, and
	 * the failure is more likely due to insane val.
	 */
	if (server == NULL)
		return (0);

	if (skip_master && strcasecmp(server, yppush_master) == 0) {
		free(server);
		return (0);
	}

	/*
	 * Restrict the number of concurrent jobs: if yppush_jobs number
	 * of jobs have already been dispatched and are still pending,
	 * wait for one of them to finish so we can reuse its slot.
	 */
	while (yppush_running_jobs >= yppush_jobs && (yppush_svc_run (yppush_timeout) > 0))
		;

	/* Cleared for takeoff: set everything in motion. */
	if (yp_push(server, yppush_mapname, yppush_transid)) {
		free(server);
		return(yp_errno);
	}

	/* Bump the job counter and transaction ID. */
	yppush_running_jobs++;
	yppush_transid++;
	free(server);
	return (0);
}