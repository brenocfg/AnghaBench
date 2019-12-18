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
struct msqid_ds {int dummy; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  Exit (int) ; 
 int /*<<< orphan*/  IPC_RMID ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  ResetClockRate () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  mqid ; 
 int msgctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct msqid_ds*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 

void
Cleanup(void)
{
	ResetClockRate();

	if (msgctl(mqid, IPC_RMID, (struct msqid_ds *)0) == -1) {
		if (errno != EINVAL) {
			msyslog(LOG_ERR, "remove message queue: %m");
			perror("adjtimed: remove message queue");
		}
	}

	Exit(2);
}