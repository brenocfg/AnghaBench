#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tv_sec; } ;
struct TYPE_3__ {int tv_sec; } ;
struct sigaction {TYPE_2__ it_value; TYPE_1__ it_interval; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct itimerval {TYPE_2__ it_value; TYPE_1__ it_interval; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;
typedef  int /*<<< orphan*/  itv ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  log_debugx (char*,...) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int setitimer (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigalrm_handler ; 
 int /*<<< orphan*/  sigalrm_handler_fatal ; 
 int sigalrm_received ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

void
set_timeout(int timeout, int fatal)
{
	struct sigaction sa;
	struct itimerval itv;
	int error;

	if (timeout <= 0) {
		log_debugx("session timeout disabled");
		bzero(&itv, sizeof(itv));
		error = setitimer(ITIMER_REAL, &itv, NULL);
		if (error != 0)
			log_err(1, "setitimer");
		sigalrm_received = false;
		return;
	}

	sigalrm_received = false;
	bzero(&sa, sizeof(sa));
	if (fatal)
		sa.sa_handler = sigalrm_handler_fatal;
	else
		sa.sa_handler = sigalrm_handler;
	sigfillset(&sa.sa_mask);
	error = sigaction(SIGALRM, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");

	/*
	 * First SIGALRM will arive after conf_timeout seconds.
	 * If we do nothing, another one will arrive a second later.
	 */
	log_debugx("setting session timeout to %d seconds", timeout);
	bzero(&itv, sizeof(itv));
	itv.it_interval.tv_sec = 1;
	itv.it_value.tv_sec = timeout;
	error = setitimer(ITIMER_REAL, &itv, NULL);
	if (error != 0)
		log_err(1, "setitimer");
}