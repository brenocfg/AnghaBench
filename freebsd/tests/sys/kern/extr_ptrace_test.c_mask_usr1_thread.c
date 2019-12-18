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
typedef  int /*<<< orphan*/  pthread_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_REQUIRE (int) ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void *
mask_usr1_thread(void *arg)
{
	pthread_barrier_t *pbarrier;
	sigset_t sigmask;

	pbarrier = (pthread_barrier_t*)arg;

	sigemptyset(&sigmask);
	sigaddset(&sigmask, SIGUSR1);
	CHILD_REQUIRE(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) == 0);

	/* Sync up with other thread after sigmask updated. */
	pthread_barrier_wait(pbarrier);

	for (;;)
		sleep(60);

	return (NULL);
}