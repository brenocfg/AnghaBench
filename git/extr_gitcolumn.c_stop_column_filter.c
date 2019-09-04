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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  column_process ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int fd_out ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish_command (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 

int stop_column_filter(void)
{
	if (fd_out == -1)
		return -1;

	fflush(stdout);
	close(1);
	finish_command(&column_process);
	dup2(fd_out, 1);
	close(fd_out);
	fd_out = -1;
	return 0;
}