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
 int /*<<< orphan*/  SIG_SETMASK ; 
 int errno ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 int pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigfillset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int thr_sigsetmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void 
ub_thread_blocksigs(void)
{
#if defined(HAVE_PTHREAD) || defined(HAVE_SOLARIS_THREADS) || defined(HAVE_SIGPROCMASK)
#  if defined(HAVE_PTHREAD) || defined(HAVE_SOLARIS_THREADS)
	int err;
#  endif
	sigset_t sigset;
	sigfillset(&sigset);
#ifdef HAVE_PTHREAD
	if((err=pthread_sigmask(SIG_SETMASK, &sigset, NULL)))
		fatal_exit("pthread_sigmask: %s", strerror(err));
#else
#  ifdef HAVE_SOLARIS_THREADS
	if((err=thr_sigsetmask(SIG_SETMASK, &sigset, NULL)))
		fatal_exit("thr_sigsetmask: %s", strerror(err));
#  else 
	/* have nothing, do single process signal mask */
	if(sigprocmask(SIG_SETMASK, &sigset, NULL))
		fatal_exit("sigprocmask: %s", strerror(errno));
#  endif /* HAVE_SOLARIS_THREADS */
#endif /* HAVE_PTHREAD */
#endif /* have signal stuff */
}