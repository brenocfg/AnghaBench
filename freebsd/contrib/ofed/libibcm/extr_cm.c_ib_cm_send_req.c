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
struct ib_user_path_rec {int dummy; } ;
struct ib_ucm_req {uintptr_t primary_path; uintptr_t alternate_path; uintptr_t data; scalar_t__ len; int /*<<< orphan*/  srq; int /*<<< orphan*/  max_cm_retries; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  local_cm_response_timeout; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  remote_cm_response_timeout; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  peer_to_peer; int /*<<< orphan*/  sid; int /*<<< orphan*/  psn; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  qpn; int /*<<< orphan*/  id; } ;
struct ib_cm_req_param {scalar_t__ private_data_len; scalar_t__ private_data; int /*<<< orphan*/  alternate_path; int /*<<< orphan*/  primary_path; int /*<<< orphan*/  srq; int /*<<< orphan*/  max_cm_retries; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  local_cm_response_timeout; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  remote_cm_response_timeout; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  peer_to_peer; int /*<<< orphan*/  service_id; int /*<<< orphan*/  starting_psn; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  qp_num; } ;
struct ib_cm_id {TYPE_1__* device; int /*<<< orphan*/  handle; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_CREATE_MSG_CMD (void*,struct ib_ucm_req*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IB_USER_CM_CMD_SEND_REQ ; 
 struct ib_user_path_rec* alloca (int) ; 
 int /*<<< orphan*/  ibv_copy_path_rec_to_kern (struct ib_user_path_rec*,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,void*,int) ; 

int ib_cm_send_req(struct ib_cm_id *cm_id, struct ib_cm_req_param *param)
{
	struct ib_user_path_rec p_path;
	struct ib_user_path_rec *a_path;
	struct ib_ucm_req *cmd;
	void *msg;
	int result;
	int size;

	if (!param || !param->primary_path)
		return ERR(EINVAL);

	CM_CREATE_MSG_CMD(msg, cmd, IB_USER_CM_CMD_SEND_REQ, size);
	cmd->id				= cm_id->handle;
	cmd->qpn			= param->qp_num;
	cmd->qp_type			= param->qp_type;
	cmd->psn			= param->starting_psn;
        cmd->sid			= param->service_id;
        cmd->peer_to_peer               = param->peer_to_peer;
        cmd->responder_resources        = param->responder_resources;
        cmd->initiator_depth            = param->initiator_depth;
        cmd->remote_cm_response_timeout = param->remote_cm_response_timeout;
        cmd->flow_control               = param->flow_control;
        cmd->local_cm_response_timeout  = param->local_cm_response_timeout;
        cmd->retry_count                = param->retry_count;
        cmd->rnr_retry_count            = param->rnr_retry_count;
        cmd->max_cm_retries             = param->max_cm_retries;
        cmd->srq                        = param->srq;

	ibv_copy_path_rec_to_kern(&p_path, param->primary_path);
	cmd->primary_path = (uintptr_t) &p_path;
		
	if (param->alternate_path) {
		a_path = alloca(sizeof(*a_path));
		if (!a_path)
			return ERR(ENOMEM);

		ibv_copy_path_rec_to_kern(a_path, param->alternate_path);
		cmd->alternate_path = (uintptr_t) a_path;
	}

	if (param->private_data && param->private_data_len) {
		cmd->data = (uintptr_t) param->private_data;
		cmd->len  = param->private_data_len;
	}

	result = write(cm_id->device->fd, msg, size);
	if (result != size)
		return (result >= 0) ? ERR(ENODATA) : -1;

	return 0;
}