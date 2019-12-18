#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ibv_qp {TYPE_4__* context; int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct ibv_kern_spec {TYPE_1__ hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; } ;
struct ibv_flow_spec {TYPE_2__ hdr; } ;
struct ibv_flow_attr {int num_of_specs; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; int /*<<< orphan*/  type; } ;
struct ibv_flow {int /*<<< orphan*/  handle; TYPE_4__* context; } ;
struct ibv_create_flow_resp {int /*<<< orphan*/  flow_handle; } ;
struct TYPE_7__ {int num_of_specs; int size; int /*<<< orphan*/  flags; int /*<<< orphan*/  port; int /*<<< orphan*/  priority; int /*<<< orphan*/  type; } ;
struct ibv_create_flow {TYPE_3__ flow_attr; int /*<<< orphan*/  qp_handle; } ;
typedef  int /*<<< orphan*/  resp ;
struct TYPE_8__ {int /*<<< orphan*/  cmd_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_FLOW ; 
 int /*<<< orphan*/  IBV_INIT_CMD_RESP_EX_VCMD (struct ibv_create_flow*,size_t,size_t,int /*<<< orphan*/ ,struct ibv_create_flow_resp*,int) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ibv_create_flow_resp*,int) ; 
 struct ibv_create_flow* alloca (size_t) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct ibv_flow*) ; 
 int ib_spec_to_kern_spec (void*,void*) ; 
 struct ibv_flow* malloc (int) ; 
 int /*<<< orphan*/  memset (struct ibv_create_flow*,int /*<<< orphan*/ ,size_t) ; 
 size_t write (int /*<<< orphan*/ ,struct ibv_create_flow*,size_t) ; 

struct ibv_flow *ibv_cmd_create_flow(struct ibv_qp *qp,
				     struct ibv_flow_attr *flow_attr)
{
	struct ibv_create_flow *cmd;
	struct ibv_create_flow_resp resp;
	struct ibv_flow *flow_id;
	size_t cmd_size;
	size_t written_size;
	int i, err;
	void *kern_spec;
	void *ib_spec;

	cmd_size = sizeof(*cmd) + (flow_attr->num_of_specs *
				  sizeof(struct ibv_kern_spec));
	cmd = alloca(cmd_size);
	flow_id = malloc(sizeof(*flow_id));
	if (!flow_id)
		return NULL;
	memset(cmd, 0, cmd_size);

	cmd->qp_handle = qp->handle;

	cmd->flow_attr.type = flow_attr->type;
	cmd->flow_attr.priority = flow_attr->priority;
	cmd->flow_attr.num_of_specs = flow_attr->num_of_specs;
	cmd->flow_attr.port = flow_attr->port;
	cmd->flow_attr.flags = flow_attr->flags;

	kern_spec = cmd + 1;
	ib_spec = flow_attr + 1;
	for (i = 0; i < flow_attr->num_of_specs; i++) {
		err = ib_spec_to_kern_spec(ib_spec, kern_spec);
		if (err) {
			errno = err;
			goto err;
		}
		cmd->flow_attr.size +=
			((struct ibv_kern_spec *)kern_spec)->hdr.size;
		kern_spec += ((struct ibv_kern_spec *)kern_spec)->hdr.size;
		ib_spec += ((struct ibv_flow_spec *)ib_spec)->hdr.size;
	}

	written_size = sizeof(*cmd) + cmd->flow_attr.size;
	IBV_INIT_CMD_RESP_EX_VCMD(cmd, written_size, written_size, CREATE_FLOW,
				  &resp, sizeof(resp));
	if (write(qp->context->cmd_fd, cmd, written_size) != written_size)
		goto err;

	(void) VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof(resp));

	flow_id->context = qp->context;
	flow_id->handle = resp.flow_handle;
	return flow_id;
err:
	free(flow_id);
	return NULL;
}