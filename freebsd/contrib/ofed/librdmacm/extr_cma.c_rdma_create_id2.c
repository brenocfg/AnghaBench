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
struct ucma_abi_create_id_resp {int /*<<< orphan*/  id; } ;
struct ucma_abi_create_id {uintptr_t uid; int ps; int qp_type; } ;
struct rdma_event_channel {int dummy; } ;
struct rdma_cm_id {TYPE_1__* channel; } ;
struct cma_id_private {struct rdma_cm_id id; int /*<<< orphan*/  handle; } ;
typedef  enum rdma_port_space { ____Placeholder_rdma_port_space } rdma_port_space ;
typedef  enum ibv_qp_type { ____Placeholder_ibv_qp_type } ibv_qp_type ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMA_INIT_CMD_RESP (struct ucma_abi_create_id*,int,int /*<<< orphan*/ ,struct ucma_abi_create_id_resp*,int) ; 
 int /*<<< orphan*/  CREATE_ID ; 
 int /*<<< orphan*/  ENOMEM ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALGRIND_MAKE_MEM_DEFINED (struct ucma_abi_create_id_resp*,int) ; 
 struct cma_id_private* ucma_alloc_id (struct rdma_event_channel*,void*,int,int) ; 
 int /*<<< orphan*/  ucma_free_id (struct cma_id_private*) ; 
 int ucma_init () ; 
 int /*<<< orphan*/  ucma_insert_id (struct cma_id_private*) ; 
 int write (int /*<<< orphan*/ ,struct ucma_abi_create_id*,int) ; 

__attribute__((used)) static int rdma_create_id2(struct rdma_event_channel *channel,
			   struct rdma_cm_id **id, void *context,
			   enum rdma_port_space ps, enum ibv_qp_type qp_type)
{
	struct ucma_abi_create_id_resp resp;
	struct ucma_abi_create_id cmd;
	struct cma_id_private *id_priv;
	int ret;

	ret = ucma_init();
	if (ret)
		return ret;

	id_priv = ucma_alloc_id(channel, context, ps, qp_type);
	if (!id_priv)
		return ERR(ENOMEM);

	CMA_INIT_CMD_RESP(&cmd, sizeof cmd, CREATE_ID, &resp, sizeof resp);
	cmd.uid = (uintptr_t) id_priv;
	cmd.ps = ps;
	cmd.qp_type = qp_type;

	ret = write(id_priv->id.channel->fd, &cmd, sizeof cmd);
	if (ret != sizeof cmd)
		goto err;

	VALGRIND_MAKE_MEM_DEFINED(&resp, sizeof resp);

	id_priv->handle = resp.id;
	ucma_insert_id(id_priv);
	*id = &id_priv->id;
	return 0;

err:	ucma_free_id(id_priv);
	return ret;
}