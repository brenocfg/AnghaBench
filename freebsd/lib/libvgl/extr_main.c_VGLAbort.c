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
 int SIGBUS ; 
 int SIGINT ; 
 int SIGSEGV ; 
 int SIGTERM ; 
 int SIGUSR2 ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SIG_UNBLOCK ; 
 int VGLAbortPending ; 
 int /*<<< orphan*/  VGLEnd () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
VGLAbort(int arg)
{
  sigset_t mask;

  VGLAbortPending = 1;
  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGUSR2, SIG_IGN);
  if (arg == SIGBUS || arg == SIGSEGV) {
    signal(arg, SIG_DFL);
    sigemptyset(&mask);
    sigaddset(&mask, arg);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    VGLEnd();
    kill(getpid(), arg);
  }
}