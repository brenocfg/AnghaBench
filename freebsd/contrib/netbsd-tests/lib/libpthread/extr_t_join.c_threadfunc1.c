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
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_EQ (int,int) ; 
 int EDEADLK ; 
 int ESRCH ; 
 int /*<<< orphan*/  PTHREAD_REQUIRE (int) ; 
 uintptr_t STACKSIZE ; 
 uintptr_t __arraycount (int /*<<< orphan*/ *) ; 
 int check_stack_alignment () ; 
 int error ; 
 scalar_t__ pthread_attr_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_attr_setstacksize (int /*<<< orphan*/ *,uintptr_t) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int pthread_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  threadfunc2 ; 

__attribute__((used)) static void *
threadfunc1(void *arg)
{
	pthread_t thread[25];
	pthread_t caller;
	void *val = NULL;
	uintptr_t i;
	int rv;
	pthread_attr_t attr;

	caller = pthread_self();

#ifdef CHECK_STACK_ALIGNMENT
	/*
	 * Check alignment of thread stack, if supported.
	 */
	ATF_REQUIRE(check_stack_alignment());
#endif

	/*
	 * The behavior is undefined, but should error
	 * out, if we try to join the calling thread.
	 */
	rv = pthread_join(caller, NULL);

	/*
	 * The specification recommends EDEADLK.
	 */
	ATF_REQUIRE(rv != 0);
	ATF_REQUIRE_EQ(rv, EDEADLK);

	ATF_REQUIRE(pthread_attr_init(&attr) == 0);

	for (i = 0; i < __arraycount(thread); i++) {

		error = true;

		ATF_REQUIRE(pthread_attr_setstacksize(&attr, STACKSIZE * (i + 1)) == 0);

		rv = pthread_create(&thread[i], &attr, threadfunc2, (void *)i);

		ATF_REQUIRE_EQ(rv, 0);

		/*
		 * Check join and exit condition.
		 */
		PTHREAD_REQUIRE(pthread_join(thread[i], &val));

		ATF_REQUIRE_EQ(error, false);

		ATF_REQUIRE(val != NULL);
		ATF_REQUIRE(val == (void *)(i + 1));

		/*
		 * Once the thread has returned, ESRCH should
		 * again follow if we try to join it again.
		 */
		rv = pthread_join(thread[i], NULL);

		ATF_REQUIRE_EQ(rv, ESRCH);

		/*
		 * Try to detach the exited thread.
		 */
		rv = pthread_detach(thread[i]);

		ATF_REQUIRE(rv != 0);
	}

	ATF_REQUIRE(pthread_attr_destroy(&attr) == 0);

	pthread_exit(NULL);

	return NULL;
}