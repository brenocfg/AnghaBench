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
typedef  scalar_t__ ub_thread_type ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  log_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

void ub_thr_fork_wait(ub_thread_type thread)
{
	int status = 0;
	if(waitpid((pid_t)thread, &status, 0) == -1)
		log_err("waitpid(%d): %s", (int)thread, strerror(errno));
	if(status != 0)
		log_warn("process %d abnormal exit with status %d",
			(int)thread, status);
}