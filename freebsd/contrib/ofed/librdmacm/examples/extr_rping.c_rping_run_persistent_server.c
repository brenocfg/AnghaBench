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
struct rping_cb {scalar_t__ state; int /*<<< orphan*/  persistent_server_thread; int /*<<< orphan*/  sem; } ;
typedef  int /*<<< orphan*/  pthread_attr_t ;

/* Variables and functions */
 scalar_t__ CONNECT_REQUEST ; 
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 struct rping_cb* clone_cb (struct rping_cb*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int pthread_attr_init (int /*<<< orphan*/ *) ; 
 int pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct rping_cb*) ; 
 int rping_bind_server (struct rping_cb*) ; 
 int /*<<< orphan*/  rping_persistent_server_thread ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_run_persistent_server(struct rping_cb *listening_cb)
{
	int ret;
	struct rping_cb *cb;
	pthread_attr_t attr;

	ret = rping_bind_server(listening_cb);
	if (ret)
		return ret;

	/*
	 * Set persistent server threads to DEATCHED state so
	 * they release all their resources when they exit.
	 */
	ret = pthread_attr_init(&attr);
	if (ret) {
		perror("pthread_attr_init");
		return ret;
	}
	ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if (ret) {
		perror("pthread_attr_setdetachstate");
		return ret;
	}

	while (1) {
		sem_wait(&listening_cb->sem);
		if (listening_cb->state != CONNECT_REQUEST) {
			fprintf(stderr, "wait for CONNECT_REQUEST state %d\n",
				listening_cb->state);
			return -1;
		}

		cb = clone_cb(listening_cb);
		if (!cb)
			return -1;

		ret = pthread_create(&cb->persistent_server_thread, &attr, rping_persistent_server_thread, cb);
		if (ret) {
			perror("pthread_create");
			return ret;
		}
	}
	return 0;
}