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
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTSTP ; 
 void SIG_DFL (int) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  STOP_SIGNAL ; 
 int /*<<< orphan*/  dont_repeat () ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  get_prompt () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,void (*) (int)) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
stop_sig (int signo)
{
#if STOP_SIGNAL == SIGTSTP
  signal (SIGTSTP, SIG_DFL);
#if HAVE_SIGPROCMASK
  {
    sigset_t zero;

    sigemptyset (&zero);
    sigprocmask (SIG_SETMASK, &zero, 0);
  }
#elif HAVE_SIGSETMASK
  sigsetmask (0);
#endif
  kill (getpid (), SIGTSTP);
  signal (SIGTSTP, stop_sig);
#else
  signal (STOP_SIGNAL, stop_sig);
#endif
  printf_unfiltered ("%s", get_prompt ());
  gdb_flush (gdb_stdout);

  /* Forget about any previous command -- null line now will do nothing.  */
  dont_repeat ();
}