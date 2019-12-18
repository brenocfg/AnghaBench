#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ucma_abi_accept {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__* channel; } ;
struct cma_id_private {TYPE_2__ id; int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCEPT ; 
 int /*<<< orphan*/  CMA_INIT_CMD (struct ucma_abi_accept*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENODATA ; 
 int ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_MAX_INIT_DEPTH ; 
 int /*<<< orphan*/  RDMA_MAX_RESP_RES ; 
 int /*<<< orphan*/  ucma_modify_qp_err (TYPE_2__*) ; 
 int ucma_modify_qp_rtr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ucma_modify_qp_rts (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,struct ucma_abi_accept*,int) ; 

__attribute__((used)) static int ucma_process_conn_resp(struct cma_id_private *id_priv)
{
	struct ucma_abi_accept cmd;
	int ret;

	ret = ucma_modify_qp_rtr(&id_priv->id, RDMA_MAX_RESP_RES);
	if (ret)
		goto err;

	ret = ucma_modify_qp_rts(&id_priv->id, RDMA_MAX_INIT_DEPTH);
	if (ret)
		goto err;

	CMA_INIT_CMD(&cmd, sizeof cmd, ACCEPT);
	cmd.id = id_priv->handle;

	ret = write(id_priv->id.channel->fd, &cmd, sizeof cmd);
	if (ret != sizeof cmd) {
		ret = (ret >= 0) ? ERR(ENODATA) : -1;
		goto err;
	}

	return 0;
err:
	ucma_modify_qp_err(&id_priv->id);
	return ret;
}