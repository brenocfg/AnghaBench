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
 int sender_shmid ; 
 int shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
cleanup(void)
{

	/*
	 * If we're the sender, and it exists, remove the shared memory area.
	 */
	if (child_pid != 0 && sender_shmid != -1) {
		if (shmctl(sender_shmid, IPC_RMID, NULL) == -1)
			warn("shmctl IPC_RMID");
	}
}