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
 int /*<<< orphan*/  IPC_RMID ; 
 scalar_t__ child_pid ; 
 int semctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sender_semid ; 
 int /*<<< orphan*/  warn (char*) ; 

void
cleanup()
{

	/*
	 * If we're the sender, and it exists, remove the message queue.
	 */
	if (child_pid != 0 && sender_semid != -1) {
		if (semctl(sender_semid, 0, IPC_RMID) == -1)
			warn("semctl IPC_RMID");
	}
}