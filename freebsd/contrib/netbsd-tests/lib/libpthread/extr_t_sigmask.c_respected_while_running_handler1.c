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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGUSR2 ; 
 int flag ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  thr_usr1 ; 

__attribute__((used)) static void
respected_while_running_handler1(int sig, siginfo_t *info, void *ctx)
{

	kill(getpid(), SIGUSR2);
	/*
	 * If the mask is properly set, SIGUSR2 will not be handled
	 * by the current thread until this handler returns.
	 */
	flag = 1;
	thr_usr1 = pthread_self();
}