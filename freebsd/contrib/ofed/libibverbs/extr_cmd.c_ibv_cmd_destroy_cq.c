#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ibv_destroy_cq_resp {scalar_t__ comp_events_reported; scalar_t__ async_events_reported; } ;
struct ibv_destroy_cq {scalar_t__ reserved; int /*<<< orphan*/  cq_handle; } ;
struct ibv_cq {scalar_t__ comp_events_completed; scalar_t__ async_events_completed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_CQ ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_destroy_cq*,int,int /*<<< orphan*/ ,struct ibv_destroy_cq_resp*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_destroy_cq_resp*,int) ; 
 int errno ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,struct ibv_destroy_cq*,int) ; 

int ibv_cmd_destroy_cq(struct ibv_cq *cq)
{
	struct ibv_destroy_cq      cmd;
	struct ibv_destroy_cq_resp resp;

	IBV_INIT_CMD_RESP(&cmd, sizeof cmd, DESTROY_CQ, &resp, sizeof resp);
	cmd.cq_handle = cq->handle;
	cmd.reserved  = 0;

	if (write(cq->context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	pthread_mutex_lock(&cq->mutex);
	while (cq->comp_events_completed  != resp.comp_events_reported ||
	       cq->async_events_completed != resp.async_events_reported)
		pthread_cond_wait(&cq->cond, &cq->mutex);
	pthread_mutex_unlock(&cq->mutex);

	return 0;
}