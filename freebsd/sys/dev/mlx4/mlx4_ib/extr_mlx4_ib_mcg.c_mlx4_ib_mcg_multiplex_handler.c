#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct mlx4_ib_demux_ctx* demux; } ;
struct mlx4_ib_dev {TYPE_1__ sriov; } ;
struct mlx4_ib_demux_ctx {int /*<<< orphan*/  mcg_table_lock; scalar_t__ flushing; } ;
struct TYPE_6__ {int method; } ;
struct ib_sa_mad {TYPE_3__ mad_hdr; scalar_t__ data; } ;
struct mcast_req {int func; struct mcast_group* group; struct ib_sa_mad sa_mad; } ;
struct mcast_group {int /*<<< orphan*/  lock; TYPE_2__* func; } ;
struct ib_sa_mcmember_data {int /*<<< orphan*/  mgid; } ;
struct ib_device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  num_pend_reqs; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  IB_MGMT_METHOD_GET_RESP 133 
#define  IB_MGMT_METHOD_SET 132 
#define  IB_SA_METHOD_DELETE 131 
#define  IB_SA_METHOD_DELETE_RESP 130 
#define  IB_SA_METHOD_GET_TABLE 129 
#define  IB_SA_METHOD_GET_TABLE_RESP 128 
 int /*<<< orphan*/  IS_ERR (struct mcast_group*) ; 
 int /*<<< orphan*/  MAX_PEND_REQS_PER_FUNC ; 
 int PTR_ERR (struct mcast_group*) ; 
 struct mcast_group* acquire_group (struct mlx4_ib_demux_ctx*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcast_req*) ; 
 struct mcast_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcg_debug_group (struct mcast_group*,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcg_warn (char*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_req (struct mcast_req*) ; 
 int /*<<< orphan*/  release_group (struct mcast_group*,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

int mlx4_ib_mcg_multiplex_handler(struct ib_device *ibdev, int port,
				  int slave, struct ib_sa_mad *sa_mad)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	struct ib_sa_mcmember_data *rec = (struct ib_sa_mcmember_data *)sa_mad->data;
	struct mlx4_ib_demux_ctx *ctx = &dev->sriov.demux[port - 1];
	struct mcast_group *group;
	struct mcast_req *req;
	int may_create = 0;

	if (ctx->flushing)
		return -EAGAIN;

	switch (sa_mad->mad_hdr.method) {
	case IB_MGMT_METHOD_SET:
		may_create = 1;
	case IB_SA_METHOD_DELETE:
		req = kzalloc(sizeof *req, GFP_KERNEL);
		if (!req)
			return -ENOMEM;

		req->func = slave;
		req->sa_mad = *sa_mad;

		mutex_lock(&ctx->mcg_table_lock);
		group = acquire_group(ctx, &rec->mgid, may_create, GFP_KERNEL);
		mutex_unlock(&ctx->mcg_table_lock);
		if (IS_ERR(group)) {
			kfree(req);
			return PTR_ERR(group);
		}
		mutex_lock(&group->lock);
		if (group->func[slave].num_pend_reqs > MAX_PEND_REQS_PER_FUNC) {
			mutex_unlock(&group->lock);
			mcg_debug_group(group, "Port %d, Func %d has too many pending requests (%d), dropping\n",
					port, slave, MAX_PEND_REQS_PER_FUNC);
			release_group(group, 0);
			kfree(req);
			return -ENOMEM;
		}
		++group->func[slave].num_pend_reqs;
		req->group = group;
		queue_req(req);
		mutex_unlock(&group->lock);
		release_group(group, 0);
		return 1; /* consumed */
	case IB_SA_METHOD_GET_TABLE:
	case IB_MGMT_METHOD_GET_RESP:
	case IB_SA_METHOD_GET_TABLE_RESP:
	case IB_SA_METHOD_DELETE_RESP:
		return 0; /* not consumed, pass-through */
	default:
		mcg_warn("In multiplex, port %d, func %d: unexpected MCMember method: 0x%x, dropping\n",
			port, slave, sa_mad->mad_hdr.method);
		return 1; /* consumed */
	}
}