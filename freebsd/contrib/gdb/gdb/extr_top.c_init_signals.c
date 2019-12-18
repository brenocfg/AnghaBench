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
 int /*<<< orphan*/  SIGFPE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIGWINCH_HANDLER ; 
 int /*<<< orphan*/  SIG_DFL ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  disconnect ; 
 int /*<<< orphan*/  do_nothing ; 
 int /*<<< orphan*/  float_handler ; 
 int /*<<< orphan*/  request_quit ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_signals (void)
{
  signal (SIGINT, request_quit);

  /* If SIGTRAP was set to SIG_IGN, then the SIG_IGN will get passed
     to the inferior and breakpoints will be ignored.  */
#ifdef SIGTRAP
  signal (SIGTRAP, SIG_DFL);
#endif

  /* If we initialize SIGQUIT to SIG_IGN, then the SIG_IGN will get
     passed to the inferior, which we don't want.  It would be
     possible to do a "signal (SIGQUIT, SIG_DFL)" after we fork, but
     on BSD4.3 systems using vfork, that can affect the
     GDB process as well as the inferior (the signal handling tables
     might be in memory, shared between the two).  Since we establish
     a handler for SIGQUIT, when we call exec it will set the signal
     to SIG_DFL for us.  */
  signal (SIGQUIT, do_nothing);
#ifdef SIGHUP
  if (signal (SIGHUP, do_nothing) != SIG_IGN)
    signal (SIGHUP, disconnect);
#endif
  signal (SIGFPE, float_handler);

#if defined(SIGWINCH) && defined(SIGWINCH_HANDLER)
  signal (SIGWINCH, SIGWINCH_HANDLER);
#endif
}