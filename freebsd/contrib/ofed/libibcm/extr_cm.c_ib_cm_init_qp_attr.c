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
struct ibv_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ibv_kern_qp_attr {int qp_attr_mask; } ;
struct ib_ucm_init_qp_attr {int /*<<< orphan*/  qp_state; int /*<<< orphan*/  id; } ;
struct ib_cm_id {TYPE_1__* device; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD_RESP (void*,struct ib_ucm_init_qp_attr*,struct ibv_kern_qp_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODATA ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_INIT_QP_ATTR ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_kern_qp_attr*,int) ; 
 int /*<<< orphan*/  ibv_copy_qp_attr_from_kern (struct ibv_qp_attr*,struct ibv_kern_qp_attr*) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_init_qp_attr(struct ib_cm_id *cm_id,
		       struct ibv_qp_attr *qp_attr,
		       int *qp_attr_mask)
{
	struct ibv_kern_qp_attr *resp;
	struct ib_ucm_init_qp_attr *cmd;
	void *msg;
	int result;
	int size;

	if (!qp_attr || !qp_attr_mask)
		return ERR(EINVAL);

	CM_CREATE_MSG_CMD_RESP(msg, cmd, resp, IB_USER_CM_CMD_INIT_QP_ATTR, size);
	cmd->id = cm_id->handle;
	cmd->qp_state = qp_attr->qp_state;

	result = write(cm_id->device->fd, msg, size);
	if (result != size)
		return (result >= 0) ? ERR(ENODATA) : result;

	VALGRIND_MAKE_MEM_DEFINED(resp, sizeof *resp);

	*qp_attr_mask = resp->qp_attr_mask;
	ibv_copy_qp_attr_from_kern(qp_attr, resp);

	return 0;
}