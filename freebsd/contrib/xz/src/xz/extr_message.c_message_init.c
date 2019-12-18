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
struct sigaction {int /*<<< orphan*/ * sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 scalar_t__* message_progress_sigs ; 
 int /*<<< orphan*/  message_signal_handler () ; 
 int /*<<< orphan*/  progress_automatic ; 
 int /*<<< orphan*/  progress_signal_handler ; 
 scalar_t__ sigaction (scalar_t__,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

extern void
message_init(void)
{
	// If --verbose is used, we use a progress indicator if and only
	// if stderr is a terminal. If stderr is not a terminal, we print
	// verbose information only after finishing the file. As a special
	// exception, even if --verbose was not used, user can send SIGALRM
	// to make us print progress information once without automatic
	// updating.
	progress_automatic = isatty(STDERR_FILENO);

	// Commented out because COLUMNS is rarely exported to environment.
	// Most users have at least 80 columns anyway, let's think something
	// fancy here if enough people complain.
/*
	if (progress_automatic) {
		// stderr is a terminal. Check the COLUMNS environment
		// variable to see if the terminal is wide enough. If COLUMNS
		// doesn't exist or it has some unparsable value, we assume
		// that the terminal is wide enough.
		const char *columns_str = getenv("COLUMNS");
		if (columns_str != NULL) {
			char *endptr;
			const long columns = strtol(columns_str, &endptr, 10);
			if (*endptr != '\0' || columns < 80)
				progress_automatic = false;
		}
	}
*/

#ifdef SIGALRM
	// Establish the signal handlers which set a flag to tell us that
	// progress info should be updated.
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &progress_signal_handler;

	for (size_t i = 0; message_progress_sigs[i] != 0; ++i)
		if (sigaction(message_progress_sigs[i], &sa, NULL))
			message_signal_handler();
#endif

	return;
}