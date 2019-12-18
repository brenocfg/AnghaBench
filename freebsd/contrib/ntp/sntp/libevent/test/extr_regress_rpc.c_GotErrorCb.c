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
 scalar_t__ EVRPC_STATUS_ERR_TIMEOUT ; 
 int /*<<< orphan*/  event_loopexit (int /*<<< orphan*/ *) ; 
 scalar_t__ kill_complete (struct kill*) ; 
 int test_ok ; 

__attribute__((used)) static void
GotErrorCb(struct evrpc_status *status,
    struct msg *msg, struct kill *kill, void *arg)
{
	if (status->error != EVRPC_STATUS_ERR_TIMEOUT)
		goto done;

	/* should never be complete but just to check */
	if (kill_complete(kill) == 0)
		goto done;

	test_ok += 1;

done:
	event_loopexit(NULL);
}