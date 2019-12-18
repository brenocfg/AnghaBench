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
struct sigaction {int /*<<< orphan*/  sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  mark_exit_flag ; 
 int /*<<< orphan*/  mark_hup_flag ; 
 int /*<<< orphan*/  mark_usr1_flag ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  saved_sigset ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_signals()
{
	struct sigaction act;

	sigemptyset(&act.sa_mask);
	act.sa_handler = mark_exit_flag;
	act.sa_flags = 0;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	act.sa_handler = mark_hup_flag;
	sigaction(SIGHUP, &act, NULL);
	sigaction(SIGCONT, &act, NULL);
#ifndef HAVE_OLD_LINUX_THREADS
	act.sa_handler = mark_usr1_flag;
	sigaction(SIGUSR1, &act, NULL);
#endif
	pthread_sigmask(SIG_SETMASK, &saved_sigset, NULL);
}