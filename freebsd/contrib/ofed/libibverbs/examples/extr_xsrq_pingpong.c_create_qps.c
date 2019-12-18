#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_send_wr; int max_send_sge; } ;
struct ibv_qp_init_attr_ex {int /*<<< orphan*/  pd; int /*<<< orphan*/  comp_mask; TYPE_1__ cap; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  xrcd; } ;
struct ibv_qp_attr {int qp_access_flags; int /*<<< orphan*/  port_num; scalar_t__ pkey_index; void* qp_state; } ;
struct TYPE_4__ {int num_clients; int num_tests; void** send_qp; int /*<<< orphan*/  ib_port; int /*<<< orphan*/  context; int /*<<< orphan*/  pd; int /*<<< orphan*/  send_cq; void** recv_qp; int /*<<< orphan*/  xrcd; } ;

/* Variables and functions */
 int IBV_ACCESS_REMOTE_READ ; 
 int IBV_ACCESS_REMOTE_WRITE ; 
 void* IBV_QPS_INIT ; 
 int /*<<< orphan*/  IBV_QPT_XRC_RECV ; 
 int /*<<< orphan*/  IBV_QPT_XRC_SEND ; 
 int IBV_QP_ACCESS_FLAGS ; 
 int /*<<< orphan*/  IBV_QP_INIT_ATTR_PD ; 
 int /*<<< orphan*/  IBV_QP_INIT_ATTR_XRCD ; 
 int IBV_QP_PKEY_INDEX ; 
 int IBV_QP_PORT ; 
 int IBV_QP_STATE ; 
 TYPE_2__ ctx ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 void* ibv_create_qp_ex (int /*<<< orphan*/ ,struct ibv_qp_init_attr_ex*) ; 
 scalar_t__ ibv_modify_qp (void*,struct ibv_qp_attr*,int) ; 
 int /*<<< orphan*/  memset (struct ibv_qp_init_attr_ex*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int create_qps(void)
{
	struct ibv_qp_init_attr_ex init;
	struct ibv_qp_attr mod;
	int i;

	for (i = 0; i < ctx.num_clients; ++i) {

		memset(&init, 0, sizeof init);
		init.qp_type = IBV_QPT_XRC_RECV;
		init.comp_mask = IBV_QP_INIT_ATTR_XRCD;
		init.xrcd = ctx.xrcd;

		ctx.recv_qp[i] = ibv_create_qp_ex(ctx.context, &init);
		if (!ctx.recv_qp[i])  {
			fprintf(stderr, "Couldn't create recv QP[%d] errno %d\n",
				i, errno);
			return 1;
		}

		mod.qp_state        = IBV_QPS_INIT;
		mod.pkey_index      = 0;
		mod.port_num        = ctx.ib_port;
		mod.qp_access_flags = IBV_ACCESS_REMOTE_WRITE | IBV_ACCESS_REMOTE_READ;

		if (ibv_modify_qp(ctx.recv_qp[i], &mod,
				  IBV_QP_STATE | IBV_QP_PKEY_INDEX |
				  IBV_QP_PORT | IBV_QP_ACCESS_FLAGS)) {
			fprintf(stderr, "Failed to modify recv QP[%d] to INIT\n", i);
			return 1;
		}

		memset(&init, 0, sizeof init);
		init.qp_type	      = IBV_QPT_XRC_SEND;
		init.send_cq	      = ctx.send_cq;
		init.cap.max_send_wr  = ctx.num_clients * ctx.num_tests;
		init.cap.max_send_sge = 1;
		init.comp_mask	      = IBV_QP_INIT_ATTR_PD;
		init.pd		      = ctx.pd;

		ctx.send_qp[i] = ibv_create_qp_ex(ctx.context, &init);
		if (!ctx.send_qp[i])  {
			fprintf(stderr, "Couldn't create send QP[%d] errno %d\n",
				i, errno);
			return 1;
		}

		mod.qp_state        = IBV_QPS_INIT;
		mod.pkey_index      = 0;
		mod.port_num        = ctx.ib_port;
		mod.qp_access_flags = 0;

		if (ibv_modify_qp(ctx.send_qp[i], &mod,
				  IBV_QP_STATE | IBV_QP_PKEY_INDEX |
				  IBV_QP_PORT | IBV_QP_ACCESS_FLAGS)) {
			fprintf(stderr, "Failed to modify send QP[%d] to INIT\n", i);
			return 1;
		}
	}

	return 0;
}