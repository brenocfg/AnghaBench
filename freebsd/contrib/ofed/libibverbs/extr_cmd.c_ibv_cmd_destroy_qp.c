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
struct ibv_qp {scalar_t__ events_completed; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cond; TYPE_1__* context; int /*<<< orphan*/  handle; } ;
struct ibv_destroy_qp_resp {scalar_t__ events_reported; } ;
struct ibv_destroy_qp {scalar_t__ reserved; int /*<<< orphan*/  qp_handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROY_QP ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP (struct ibv_destroy_qp*,int,int /*<<< orphan*/ ,struct ibv_destroy_qp_resp*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_destroy_qp_resp*,int) ; 
 int errno ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int write (int /*<<< orphan*/ ,struct ibv_destroy_qp*,int) ; 

int ibv_cmd_destroy_qp(struct ibv_qp *qp)
{
	struct ibv_destroy_qp      cmd;
	struct ibv_destroy_qp_resp resp;

	IBV_INIT_CMD_RESP(&cmd, sizeof cmd, DESTROY_QP, &resp, sizeof resp);
	cmd.qp_handle = qp->handle;
	cmd.reserved  = 0;

	if (write(qp->context->cmd_fd, &cmd, sizeof cmd) != sizeof cmd)
		return errno;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	pthread_mutex_lock(&qp->mutex);
	while (qp->events_completed != resp.events_reported)
		pthread_cond_wait(&qp->cond, &qp->mutex);
	pthread_mutex_unlock(&qp->mutex);

	return 0;
}