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
struct timespec {int tv_sec; } ;
struct nmreq_opt_csb {int dummy; } ;
struct TestContext {int /*<<< orphan*/ * sem; } ;
typedef  int /*<<< orphan*/  sem_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 void* THRET_FAILURE ; 
 void* THRET_SUCCESS ; 
 int /*<<< orphan*/  clear_options (struct TestContext*) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int errno ; 
 int port_register_hwall (struct TestContext*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct TestContext*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int push_csb_option (struct TestContext*,struct nmreq_opt_csb*) ; 
 int /*<<< orphan*/  sem_destroy (int /*<<< orphan*/ *) ; 
 int sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sem_timedwait (int /*<<< orphan*/ *,struct timespec*) ; 
 char* strerror (int) ; 
 int sync_kloop_stop (struct TestContext*) ; 
 int /*<<< orphan*/  sync_kloop_worker ; 

__attribute__((used)) static int
sync_kloop_conflict(struct TestContext *ctx)
{
	struct nmreq_opt_csb opt;
	pthread_t th1, th2;
	void *thret1 = THRET_FAILURE, *thret2 = THRET_FAILURE;
	struct timespec to;
	sem_t sem;
	int err = 0;
	int ret;

	ret = push_csb_option(ctx, &opt);
	if (ret != 0) {
		return ret;
	}

	ret = port_register_hwall(ctx);
	if (ret != 0) {
		return ret;
	}
	clear_options(ctx);

	ret = sem_init(&sem, 0, 0);
	if (ret != 0) {
		printf("sem_init() failed: %s\n", strerror(ret));
		return ret;
	}
	ctx->sem = &sem;

	ret = pthread_create(&th1, NULL, sync_kloop_worker, ctx);
	err |= ret;
	if (ret != 0) {
		printf("pthread_create(kloop1): %s\n", strerror(ret));
	}

	ret = pthread_create(&th2, NULL, sync_kloop_worker, ctx);
	err |= ret;
	if (ret != 0) {
		printf("pthread_create(kloop2): %s\n", strerror(ret));
	}

	/* Wait for one of the two threads to fail to start the kloop, to
	 * avoid a race condition where th1 starts the loop and stops,
	 * and after that th2 starts the loop successfully. */
	clock_gettime(CLOCK_REALTIME, &to);
	to.tv_sec += 2;
	ret = sem_timedwait(&sem, &to);
	err |= ret;
	if (ret != 0) {
		printf("sem_timedwait() failed: %s\n", strerror(errno));
	}

	err |= sync_kloop_stop(ctx);

	ret = pthread_join(th1, &thret1);
	err |= ret;
	if (ret != 0) {
		printf("pthread_join(kloop1): %s\n", strerror(ret));
	}

	ret = pthread_join(th2, &thret2);
	err |= ret;
	if (ret != 0) {
		printf("pthread_join(kloop2): %s %d\n", strerror(ret), ret);
	}

	sem_destroy(&sem);
	ctx->sem = NULL;
	if (err) {
		return err;
	}

	/* Check that one of the two failed, while the other one succeeded. */
	return ((thret1 == THRET_SUCCESS && thret2 == THRET_FAILURE) ||
			(thret1 == THRET_FAILURE && thret2 == THRET_SUCCESS))
	               ? 0
	               : -1;
}