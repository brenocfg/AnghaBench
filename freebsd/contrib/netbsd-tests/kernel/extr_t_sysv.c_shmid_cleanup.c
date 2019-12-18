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
 int /*<<< orphan*/  err (int,char*) ; 
 int read_int (char const*) ; 
 int shmctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shmid_cleanup(const char *name)
{
	int shmid;

	/*
	 * Remove the shared memory area if it exists.
	 */
	shmid = read_int(name);
	if (shmid != -1) {
		if (shmctl(shmid, IPC_RMID, NULL) == -1)
			err(1, "shmctl IPC_RMID");
	}
}