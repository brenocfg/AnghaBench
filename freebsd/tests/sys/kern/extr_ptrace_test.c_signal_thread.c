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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pthread_barrier_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigusr1_sem ; 

__attribute__((used)) static void *
signal_thread(void *arg)
{
	int err;
	sigset_t sigmask;

	pthread_barrier_t *pbarrier = (pthread_barrier_t*)arg;

	/* Wait for this thread to receive a SIGUSR1. */
	do {
		err = sem_wait(&sigusr1_sem);
		CHILD_REQUIRE(err == 0 || errno == EINTR);
	} while (err != 0 && errno == EINTR);

	/* Free our companion thread from the barrier. */
	pthread_barrier_wait(pbarrier);

	/*
	 * Swap ignore duties; the next SIGUSR1 should go to the
	 * other thread.
	 */
	CHILD_REQUIRE(sigemptyset(&sigmask) == 0);
	CHILD_REQUIRE(sigaddset(&sigmask, SIGUSR1) == 0);
	CHILD_REQUIRE(pthread_sigmask(SIG_BLOCK, &sigmask, NULL) == 0);

	/* Sync up threads after swapping signal masks. */
	pthread_barrier_wait(pbarrier);

	/* Wait until our companion has received its SIGUSR1. */
	pthread_barrier_wait(pbarrier);

	return (NULL);
}