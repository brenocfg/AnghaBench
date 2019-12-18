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
struct sigaction {void* sa_handler; int /*<<< orphan*/  sa_mask; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 void* sigchld_handler ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 void* sighup_handler ; 
 void* sigterm_handler ; 

__attribute__((used)) static void
register_signals(void)
{
	struct sigaction sa;
	int error;

	bzero(&sa, sizeof(sa));
	sa.sa_handler = sighup_handler;
	sigfillset(&sa.sa_mask);
	error = sigaction(SIGHUP, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");

	sa.sa_handler = sigterm_handler;
	error = sigaction(SIGTERM, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");

	sa.sa_handler = sigterm_handler;
	error = sigaction(SIGINT, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");

	sa.sa_handler = sigchld_handler;
	error = sigaction(SIGCHLD, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");
}