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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEM_REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  alarm_ms (int) ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem ; 
 int /*<<< orphan*/  sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sighandler ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  threadfunc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
before_start_test(const bool use_pthread)
{
	pthread_t t;

	SEM_REQUIRE(sem_init(&sem, 0, 0));
	ATF_REQUIRE(SIG_ERR != signal(SIGALRM, sighandler));

	alarm_ms(5);

	if (use_pthread) {
		PTHREAD_REQUIRE(pthread_create(&t, NULL, threadfunc, NULL));
		PTHREAD_REQUIRE(pthread_join(t, NULL));
	} else {
		threadfunc(NULL);
	}
}