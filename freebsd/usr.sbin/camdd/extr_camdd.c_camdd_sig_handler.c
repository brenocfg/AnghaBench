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
 int SIGINFO ; 
 int /*<<< orphan*/  camdd_sem ; 
 int error_exit ; 
 int need_exit ; 
 int need_status ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

void
camdd_sig_handler(int sig)
{
	if (sig == SIGINFO)
		need_status = 1;
	else {
		need_exit = 1;
		error_exit = 1;
	}

	sem_post(&camdd_sem);
}