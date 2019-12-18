#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_4__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_5__ {TYPE_1__ it_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ITIMER_REAL ; 
 int /*<<< orphan*/  SA_RESTART ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  early_output ; 
 TYPE_2__ early_output_timer ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setitimer (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void setup_early_output(void)
{
	struct sigaction sa;

	/*
	 * Set up the signal handler, minimally intrusively:
	 * we only set a single volatile integer word (not
	 * using sigatomic_t - trying to avoid unnecessary
	 * system dependencies and headers), and using
	 * SA_RESTART.
	 */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = early_output;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sa, NULL);

	/*
	 * If we can get the whole output in less than a
	 * tenth of a second, don't even bother doing the
	 * early-output thing..
	 *
	 * This is a one-time-only trigger.
	 */
	early_output_timer.it_value.tv_sec = 0;
	early_output_timer.it_value.tv_usec = 100000;
	setitimer(ITIMER_REAL, &early_output_timer, NULL);
}