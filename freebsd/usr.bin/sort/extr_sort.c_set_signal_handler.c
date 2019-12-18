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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/ * sa_sigaction; } ;
typedef  int /*<<< orphan*/  sa ;

/* Variables and functions */
 int /*<<< orphan*/  SA_SIGINFO ; 
 int /*<<< orphan*/  SIGABRT ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sig_handler ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
set_signal_handler(void)
{
	struct sigaction sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &sig_handler;
	sa.sa_flags = SA_SIGINFO;

	if (sigaction(SIGTERM, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGHUP, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGINT, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGQUIT, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGABRT, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGBUS, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGSEGV, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGUSR1, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
	if (sigaction(SIGUSR2, &sa, NULL) < 0) {
		perror("sigaction");
		return;
	}
}