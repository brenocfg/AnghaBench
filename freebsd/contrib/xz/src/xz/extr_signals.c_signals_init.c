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
struct sigaction {scalar_t__ sa_handler; scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  SIGHUP 133 
#define  SIGINT 132 
#define  SIGPIPE 131 
#define  SIGTERM 130 
#define  SIGXCPU 129 
#define  SIGXFSZ 128 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  hooked_signals ; 
 int const* message_progress_sigs ; 
 int /*<<< orphan*/  message_signal_handler () ; 
 scalar_t__ sigaction (int const,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 int signals_are_initialized ; 

extern void
signals_init(void)
{
	// List of signals for which we establish the signal handler.
	static const int sigs[] = {
		SIGINT,
		SIGTERM,
#ifdef SIGHUP
		SIGHUP,
#endif
#ifdef SIGPIPE
		SIGPIPE,
#endif
#ifdef SIGXCPU
		SIGXCPU,
#endif
#ifdef SIGXFSZ
		SIGXFSZ,
#endif
	};

	// Mask of the signals for which we have established a signal handler.
	sigemptyset(&hooked_signals);
	for (size_t i = 0; i < ARRAY_SIZE(sigs); ++i)
		sigaddset(&hooked_signals, sigs[i]);

#ifdef SIGALRM
	// Add also the signals from message.c to hooked_signals.
	for (size_t i = 0; message_progress_sigs[i] != 0; ++i)
		sigaddset(&hooked_signals, message_progress_sigs[i]);
#endif

	// Using "my_sa" because "sa" may conflict with a sockaddr variable
	// from system headers on Solaris.
	struct sigaction my_sa;

	// All the signals that we handle we also blocked while the signal
	// handler runs.
	my_sa.sa_mask = hooked_signals;

	// Don't set SA_RESTART, because we want EINTR so that we can check
	// for user_abort and cleanup before exiting. We block the signals
	// for which we have established a handler when we don't want EINTR.
	my_sa.sa_flags = 0;
	my_sa.sa_handler = &signal_handler;

	for (size_t i = 0; i < ARRAY_SIZE(sigs); ++i) {
		// If the parent process has left some signals ignored,
		// we don't unignore them.
		struct sigaction old;
		if (sigaction(sigs[i], NULL, &old) == 0
				&& old.sa_handler == SIG_IGN)
			continue;

		// Establish the signal handler.
		if (sigaction(sigs[i], &my_sa, NULL))
			message_signal_handler();
	}

	signals_are_initialized = true;

	return;
}