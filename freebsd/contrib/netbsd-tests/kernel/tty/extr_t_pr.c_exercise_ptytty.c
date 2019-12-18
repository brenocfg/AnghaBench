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
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  TIOCFLUSH ; 
 int /*<<< orphan*/  rump_sys_ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int sendsome (int,int) ; 

__attribute__((used)) static int
exercise_ptytty(int master, int slave)
{
	int error, flags;

	/*
	 * send a few bytes from master to slave and read them back
	 */
	error = sendsome(master, slave);
	if (error)
		return error;

	flags = FREAD|FWRITE;
	rump_sys_ioctl(master, TIOCFLUSH, &flags);

	/*
	 * and the same in the other direction
	 */
	error = sendsome(slave, master);
	if (error)
		return error;

	flags = FREAD|FWRITE;
	rump_sys_ioctl(master, TIOCFLUSH, &flags);
	return 0;
}