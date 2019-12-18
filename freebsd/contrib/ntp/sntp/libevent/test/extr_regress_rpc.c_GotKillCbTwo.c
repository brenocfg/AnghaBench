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
struct msg {int dummy; } ;
struct kill {int dummy; } ;
struct evrpc_status {scalar_t__ error; } ;

/* Variables and functions */
 scalar_t__ EVRPC_STATUS_ERR_NONE ; 
 int EVTAG_GET (struct kill*,char*,char**) ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int test_ok ; 

__attribute__((used)) static void
GotKillCbTwo(struct evrpc_status *status,
    struct msg *msg, struct kill *kill, void *arg)
{
	char *weapon;
	char *action;

	if (status->error != EVRPC_STATUS_ERR_NONE)
		goto done;

	if (EVTAG_GET(kill, weapon, &weapon) == -1) {
		fprintf(stderr, "get weapon\n");
		goto done;
	}
	if (EVTAG_GET(kill, action, &action) == -1) {
		fprintf(stderr, "get action\n");
		goto done;
	}

	if (strcmp(weapon, "dagger"))
		goto done;

	if (strcmp(action, "wave around like an idiot"))
		goto done;

	test_ok += 1;

done:
	if (test_ok == 2)
		event_loopexit(NULL);
}