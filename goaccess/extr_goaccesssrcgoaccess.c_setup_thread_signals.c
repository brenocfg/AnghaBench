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
struct sigaction {scalar_t__ sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  handle_signal_action ; 
 int /*<<< orphan*/  oldset ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
setup_thread_signals (void)
{
  struct sigaction act;

  act.sa_handler = handle_signal_action;
  sigemptyset (&act.sa_mask);
  act.sa_flags = 0;

  sigaction (SIGINT, &act, NULL);
  sigaction (SIGPIPE, &act, NULL);
  sigaction (SIGTERM, &act, NULL);

  /* Restore old signal mask for the main thread */
  pthread_sigmask (SIG_SETMASK, &oldset, NULL);
}