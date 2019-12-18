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
#define  SIGALRM 132 
#define  SIGHUP 131 
#define  SIGINT 130 
#define  SIGQUIT 129 
#define  SIGTERM 128 
 int /*<<< orphan*/  running ; 
 int /*<<< orphan*/  timers ; 
 int /*<<< orphan*/  tmr_run (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sig_handle(int sig)
{

	switch (sig) {
	case SIGHUP:
	case SIGINT:
	case SIGQUIT:
	case SIGTERM:
		running = 0;
		break;
	case SIGALRM:
		tmr_run(&timers);
		break;
	}
}