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
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_sigaction; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int SA_RESETHAND ; 
 int SA_RESTART ; 
 int SA_SIGINFO ; 
 int /*<<< orphan*/  SIGBUS ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int sigfillset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler ; 

__attribute__((used)) static void
setup_signals(void)
{
	struct sigaction sa;
	int r;

	sa.sa_sigaction = sighandler;
	sa.sa_flags = SA_RESTART | SA_RESETHAND | SA_SIGINFO;
	r = sigfillset(&sa.sa_mask);
	ATF_REQUIRE(r != -1);
	r = sigaction(SIGILL, &sa, NULL);
	ATF_REQUIRE(r != -1);
	r = sigaction(SIGBUS, &sa, NULL);
	ATF_REQUIRE(r != -1);
	r = sigaction(SIGSEGV, &sa, NULL);
	ATF_REQUIRE(r != -1);
}