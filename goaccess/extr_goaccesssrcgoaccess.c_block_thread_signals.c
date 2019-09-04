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
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  oldset ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
block_thread_signals (void)
{
  /* Avoid threads catching SIGINT/SIGPIPE/SIGTERM and handle them in
   * main thread */
  sigset_t sigset;
  sigemptyset (&sigset);
  sigaddset (&sigset, SIGINT);
  sigaddset (&sigset, SIGPIPE);
  sigaddset (&sigset, SIGTERM);
  pthread_sigmask (SIG_BLOCK, &sigset, &oldset);
}