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
 int /*<<< orphan*/  RB_HALT ; 
 int /*<<< orphan*/  RB_POWERCYCLE ; 
 int /*<<< orphan*/  RB_POWEROFF ; 
 int /*<<< orphan*/  Reboot ; 
#define  SIGEMT 135 
#define  SIGHUP 134 
#define  SIGINT 133 
#define  SIGTERM 132 
#define  SIGTSTP 131 
#define  SIGUSR1 130 
#define  SIGUSR2 129 
#define  SIGWINCH 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  catatonia ; 
 int /*<<< orphan*/  clean_ttys ; 
 int /*<<< orphan*/  current_state ; 
 int /*<<< orphan*/  death ; 
 int /*<<< orphan*/  death_single ; 
 int /*<<< orphan*/  howto ; 
 int /*<<< orphan*/  multi_user ; 
 int /*<<< orphan*/  read_ttys ; 
 int /*<<< orphan*/  requested_transition ; 
 int /*<<< orphan*/  reroot ; 
 int /*<<< orphan*/  runcom ; 

__attribute__((used)) static void
transition_handler(int sig)
{

	switch (sig) {
	case SIGHUP:
		if (current_state == read_ttys || current_state == multi_user ||
		    current_state == clean_ttys || current_state == catatonia)
			requested_transition = clean_ttys;
		break;
	case SIGWINCH:
	case SIGUSR2:
		howto = sig == SIGUSR2 ? RB_POWEROFF : RB_POWERCYCLE;
	case SIGUSR1:
		howto |= RB_HALT;
	case SIGINT:
		Reboot = TRUE;
	case SIGTERM:
		if (current_state == read_ttys || current_state == multi_user ||
		    current_state == clean_ttys || current_state == catatonia)
			requested_transition = death;
		else
			requested_transition = death_single;
		break;
	case SIGTSTP:
		if (current_state == runcom || current_state == read_ttys ||
		    current_state == clean_ttys ||
		    current_state == multi_user || current_state == catatonia)
			requested_transition = catatonia;
		break;
	case SIGEMT:
		requested_transition = reroot;
		break;
	default:
		requested_transition = 0;
		break;
	}
}