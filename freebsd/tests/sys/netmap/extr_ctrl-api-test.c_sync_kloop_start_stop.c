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
struct TestContext {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 void* THRET_FAILURE ; 
 void* THRET_SUCCESS ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct TestContext*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 char* strerror (int) ; 
 int sync_kloop_stop (struct TestContext*) ; 
 int /*<<< orphan*/  sync_kloop_worker ; 

__attribute__((used)) static int
sync_kloop_start_stop(struct TestContext *ctx)
{
	pthread_t th;
	void *thret = THRET_FAILURE;
	int ret;

	ret = pthread_create(&th, NULL, sync_kloop_worker, ctx);
	if (ret != 0) {
		printf("pthread_create(kloop): %s\n", strerror(ret));
		return -1;
	}

	ret = sync_kloop_stop(ctx);
	if (ret != 0) {
		return ret;
	}

	ret = pthread_join(th, &thret);
	if (ret != 0) {
		printf("pthread_join(kloop): %s\n", strerror(ret));
	}

	return thret == THRET_SUCCESS ? 0 : -1;
}