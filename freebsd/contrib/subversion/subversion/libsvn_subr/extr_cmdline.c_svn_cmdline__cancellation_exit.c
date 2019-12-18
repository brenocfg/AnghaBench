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
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  apr_signal (int,int /*<<< orphan*/ ) ; 
 scalar_t__ cancelled ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int* signal_map ; 
 int signum_cancelled ; 

void
svn_cmdline__cancellation_exit(void)
{
  int signum = 0;

  if (cancelled && signum_cancelled)
    signum = signal_map[signum_cancelled - 1];
  if (signum)
    {
#ifndef WIN32
      apr_signal(signum, SIG_DFL);
      /* No APR support for getpid() so cannot use apr_proc_kill(). */
      kill(getpid(), signum);
#endif
    }
}