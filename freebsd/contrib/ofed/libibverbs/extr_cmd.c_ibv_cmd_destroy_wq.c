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
struct ibv_wq {scalar_t__ events_completed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_destroy_wq_resp {int response_length; scalar_t__ events_reported; int /*<<< orphan*/  wq_handle; } ;
struct ibv_destroy_wq {int response_length; scalar_t__ events_reported; int /*<<< orphan*/  wq_handle; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_WQ ; 
 int EINVAL ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP_EX (struct ibv_destroy_wq_resp*,int,int /*<<< orphan*/ ,struct ibv_destroy_wq_resp*,int) ; 
 int errno ; 
 int /*<<< orphan*/  memset (struct ibv_destroy_wq_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,struct ibv_destroy_wq_resp*,int) ; 

int ibv_cmd_destroy_wq(struct ibv_wq *wq)
{
	struct ibv_destroy_wq cmd;
	struct ibv_destroy_wq_resp resp;
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));
	memset(&resp, 0, sizeof(resp));

	IBV_INIT_CMD_RESP_EX(&cmd, sizeof(cmd), DESTROY_WQ, &resp, sizeof(resp));
	cmd.wq_handle = wq->handle;

	if (write(wq->context->cmd_fd, &cmd, sizeof(cmd)) != sizeof(cmd))
		return errno;

	if (resp.response_length < sizeof(resp))
		return EINVAL;

	pthread_mutex_lock(&wq->mutex);
	while (wq->events_completed != resp.events_reported)
		pthread_cond_wait(&wq->cond, &wq->mutex);
	pthread_mutex_unlock(&wq->mutex);

	return ret;
}