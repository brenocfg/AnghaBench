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
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  bzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigchld_handler ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
register_sigchld(void)
{
	struct sigaction sa;
	int error;

	bzero(&sa, sizeof(sa));
	sa.sa_handler = sigchld_handler;
	sigfillset(&sa.sa_mask);
	error = sigaction(SIGCHLD, &sa, NULL);
	if (error != 0)
		log_err(1, "sigaction");

}