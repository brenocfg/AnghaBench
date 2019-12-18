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
struct rping_cb {scalar_t__ state; int /*<<< orphan*/  sem; int /*<<< orphan*/  child_cm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (char*) ; 
 scalar_t__ ERROR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int rdma_accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int rping_accept(struct rping_cb *cb)
{
	int ret;

	DEBUG_LOG("accepting client connection request\n");

	ret = rdma_accept(cb->child_cm_id, NULL);
	if (ret) {
		perror("rdma_accept");
		return ret;
	}

	sem_wait(&cb->sem);
	if (cb->state == ERROR) {
		fprintf(stderr, "wait for CONNECTED state %d\n", cb->state);
		return -1;
	}
	return 0;
}