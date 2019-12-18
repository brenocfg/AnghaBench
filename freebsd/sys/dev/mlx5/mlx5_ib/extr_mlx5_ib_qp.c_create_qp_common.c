#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_9__ ;
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;
typedef  struct TYPE_22__   TYPE_15__ ;
typedef  struct TYPE_21__   TYPE_14__ ;
typedef  struct TYPE_20__   TYPE_13__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ucmd ;
typedef  int u32 ;
struct mlx5_ib_resources {int /*<<< orphan*/  s1; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; int /*<<< orphan*/  s0; int /*<<< orphan*/  c0; struct ib_pd* p0; } ;
struct TYPE_23__ {int /*<<< orphan*/  event; } ;
struct mlx5_ib_qp_base {TYPE_16__ mqp; struct mlx5_ib_qp* container_mibqp; } ;
struct TYPE_32__ {int /*<<< orphan*/  buf_addr; } ;
struct TYPE_17__ {TYPE_9__ ubuffer; } ;
struct TYPE_24__ {struct mlx5_ib_qp_base base; } ;
struct TYPE_22__ {TYPE_10__ sq; TYPE_1__ rq; } ;
struct TYPE_31__ {int /*<<< orphan*/  dma; } ;
struct TYPE_28__ {scalar_t__ wqe_cnt; int /*<<< orphan*/  lock; } ;
struct TYPE_27__ {int wqe_shift; scalar_t__ wqe_cnt; int /*<<< orphan*/  lock; } ;
struct TYPE_25__ {struct mlx5_ib_qp_base base; } ;
struct mlx5_ib_qp {int flags; int wq_sig; int scat_cqe; scalar_t__ create_type; int /*<<< orphan*/  cq_recv_list; int /*<<< orphan*/  cq_send_list; int /*<<< orphan*/  qps_list; TYPE_15__ raw_packet_qp; TYPE_8__ db; TYPE_5__ sq; TYPE_4__ rq; int /*<<< orphan*/  port; int /*<<< orphan*/  has_rq; int /*<<< orphan*/  sq_signal_bits; int /*<<< orphan*/  mutex; TYPE_2__ trans_qp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  reset_flow_resource_lock; int /*<<< orphan*/  qp_list; struct mlx5_core_dev* mdev; struct mlx5_ib_resources devr; } ;
struct mlx5_ib_create_qp_resp {int dummy; } ;
struct mlx5_ib_create_qp {int flags; scalar_t__ sq_wqe_count; int rq_wqe_shift; scalar_t__ rq_wqe_count; int /*<<< orphan*/  sq_buf_addr; } ;
struct mlx5_ib_cq {int /*<<< orphan*/  list_recv_qp; int /*<<< orphan*/  list_send_qp; } ;
struct mlx5_core_dev {int dummy; } ;
struct ib_udata {int /*<<< orphan*/  inlen; } ;
struct ib_qp_init_attr {int qp_type; int create_flags; scalar_t__ sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  srq; int /*<<< orphan*/  xrcd; int /*<<< orphan*/  port_num; int /*<<< orphan*/  cap; scalar_t__ rwq_ind_tbl; } ;
struct ib_pd {TYPE_3__* uobject; } ;
typedef  scalar_t__ __u32 ;
struct TYPE_30__ {int cqn; } ;
struct TYPE_29__ {int srqn; } ;
struct TYPE_26__ {int /*<<< orphan*/  context; } ;
struct TYPE_21__ {TYPE_7__ mcq; } ;
struct TYPE_20__ {int pdn; } ;
struct TYPE_19__ {TYPE_6__ msrq; } ;
struct TYPE_18__ {int xrcdn; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSYS ; 
 int EOPNOTSUPP ; 
 int IB_QPT_RAW_PACKET ; 
 int IB_QPT_UD ; 
#define  IB_QPT_XRC_INI 129 
#define  IB_QPT_XRC_TGT 128 
 int IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK ; 
 int IB_QP_CREATE_CROSS_CHANNEL ; 
 int IB_QP_CREATE_IPOIB_UD_LSO ; 
 int IB_QP_CREATE_MANAGED_RECV ; 
 int IB_QP_CREATE_MANAGED_SEND ; 
 int IB_QP_CREATE_SCATTER_FCS ; 
 scalar_t__ IB_SIGNAL_ALL_WR ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,void*) ; 
 int /*<<< orphan*/  MLX5_CAP_ETH (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,struct ib_pd*) ; 
 int MLX5_CQE_VERSION_V1 ; 
 int MLX5_IB_DEFAULT_UIDX ; 
 int MLX5_IB_QPT_REG_UMR ; 
 int MLX5_IB_QP_BLOCK_MULTICAST_LOOPBACK ; 
 int MLX5_IB_QP_CAP_SCATTER_FCS ; 
 int MLX5_IB_QP_CROSS_CHANNEL ; 
 int MLX5_IB_QP_LSO ; 
 int MLX5_IB_QP_MANAGED_RECV ; 
 int MLX5_IB_QP_MANAGED_SEND ; 
 scalar_t__ MLX5_QP_EMPTY ; 
 int MLX5_QP_FLAG_SCATTER_CQE ; 
 int MLX5_QP_FLAG_SIGNATURE ; 
 scalar_t__ MLX5_QP_KERNEL ; 
 int MLX5_QP_PM_MIGRATED ; 
 scalar_t__ MLX5_QP_USER ; 
 int MLX5_REQ_SCAT_DATA32_CQE ; 
 int MLX5_REQ_SCAT_DATA64_CQE ; 
 int MLX5_RES_SCAT_DATA32_CQE ; 
 int MLX5_RES_SCAT_DATA64_CQE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,struct ib_pd*,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_WQE_CTRL_CQ_UPDATE ; 
 struct ib_pd* block_lb_mc ; 
 struct ib_pd* cd ; 
 struct ib_pd* cd_master ; 
 struct ib_pd* cd_slave_receive ; 
 struct ib_pd* cd_slave_send ; 
 struct ib_pd* cqe_version ; 
 struct ib_pd* cqn_rcv ; 
 struct ib_pd* cqn_snd ; 
 int create_kernel_qp (struct mlx5_ib_dev*,struct ib_qp_init_attr*,struct mlx5_ib_qp*,int**,int*,struct mlx5_ib_qp_base*) ; 
 int /*<<< orphan*/  create_qp_in ; 
 int create_raw_packet_qp (struct mlx5_ib_dev*,struct mlx5_ib_qp*,int*,struct ib_pd*) ; 
 int create_rss_raw_qp_tir (struct mlx5_ib_dev*,struct mlx5_ib_qp*,struct ib_pd*,struct ib_qp_init_attr*,struct ib_udata*) ; 
 int create_user_qp (struct mlx5_ib_dev*,struct ib_pd*,struct mlx5_ib_qp*,struct ib_udata*,struct ib_qp_init_attr*,int**,struct mlx5_ib_create_qp_resp*,int*,struct mlx5_ib_qp_base*) ; 
 struct ib_pd* cs_req ; 
 struct ib_pd* cs_res ; 
 int /*<<< orphan*/  dbr_addr ; 
 int /*<<< orphan*/  destroy_qp_kernel (struct mlx5_ib_dev*,struct mlx5_ib_qp*) ; 
 int /*<<< orphan*/  destroy_qp_user (struct ib_pd*,struct mlx5_ib_qp*,struct mlx5_ib_qp_base*) ; 
 struct ib_pd* eth_net_offloads ; 
 int /*<<< orphan*/  get_cqs (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_ib_cq**,struct mlx5_ib_cq**) ; 
 int get_qp_user_index (int /*<<< orphan*/ ,struct mlx5_ib_create_qp*,int /*<<< orphan*/ ,int*) ; 
 int get_rx_type (struct mlx5_ib_qp*,struct ib_qp_init_attr*) ; 
 scalar_t__ ib_copy_from_udata (struct mlx5_ib_create_qp*,struct ib_udata*,int) ; 
 int ilog2 (scalar_t__) ; 
 struct ib_pd* ipoib_ipoib_offloads ; 
 scalar_t__ is_connected (int) ; 
 scalar_t__ is_sqp (int) ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 struct ib_pd* latency_sensitive ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ib_pd* log_max_qp_sz ; 
 struct ib_pd* log_rq_size ; 
 struct ib_pd* log_rq_stride ; 
 struct ib_pd* log_sq_size ; 
 int mlx5_core_create_qp (struct mlx5_core_dev*,TYPE_16__*,int*,int) ; 
 int mlx5_ib_create_qp_sqpn_qp1 () ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,...) ; 
 int mlx5_ib_get_cqe_size (struct mlx5_ib_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_lock_cqs (struct mlx5_ib_cq*,struct mlx5_ib_cq*) ; 
 int /*<<< orphan*/  mlx5_ib_odp_create_qp (struct mlx5_ib_qp*) ; 
 int /*<<< orphan*/  mlx5_ib_qp_event ; 
 int /*<<< orphan*/  mlx5_ib_unlock_cqs (struct mlx5_ib_cq*,struct mlx5_ib_cq*) ; 
 int* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct ib_pd* no_sq ; 
 struct ib_pd* pm_state ; 
 int /*<<< orphan*/  qp_has_rq (struct ib_qp_init_attr*) ; 
 int /*<<< orphan*/  raw_packet_qp_copy_info (struct mlx5_ib_qp*,TYPE_15__*) ; 
 struct ib_pd* rq_type ; 
 int /*<<< orphan*/  scatter_fcs ; 
 int set_rq_size (struct mlx5_ib_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx5_ib_qp*,struct mlx5_ib_create_qp*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ib_pd* srqn_rmpn ; 
 struct ib_pd* st ; 
 TYPE_14__* to_mcq (int /*<<< orphan*/ ) ; 
 int to_mlx5_st (int) ; 
 TYPE_13__* to_mpd (struct ib_pd*) ; 
 TYPE_12__* to_msrq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mucontext (int /*<<< orphan*/ ) ; 
 TYPE_11__* to_mxrcd (int /*<<< orphan*/ ) ; 
 struct ib_pd* ulp_stateless_offload_mode ; 
 struct ib_pd* user_index ; 
 struct ib_pd* wq_signature ; 
 struct ib_pd* xrcd ; 

__attribute__((used)) static int create_qp_common(struct mlx5_ib_dev *dev, struct ib_pd *pd,
			    struct ib_qp_init_attr *init_attr,
			    struct ib_udata *udata, struct mlx5_ib_qp *qp)
{
	struct mlx5_ib_resources *devr = &dev->devr;
	int inlen = MLX5_ST_SZ_BYTES(create_qp_in);
	struct mlx5_core_dev *mdev = dev->mdev;
	struct mlx5_ib_create_qp_resp resp;
	struct mlx5_ib_cq *send_cq;
	struct mlx5_ib_cq *recv_cq;
	unsigned long flags;
	u32 uidx = MLX5_IB_DEFAULT_UIDX;
	struct mlx5_ib_create_qp ucmd;
	struct mlx5_ib_qp_base *base;
	void *qpc;
	u32 *in;
	int err;

	base = init_attr->qp_type == IB_QPT_RAW_PACKET ?
	       &qp->raw_packet_qp.rq.base :
	       &qp->trans_qp.base;

	if (init_attr->qp_type != IB_QPT_RAW_PACKET)
		mlx5_ib_odp_create_qp(qp);

	mutex_init(&qp->mutex);
	spin_lock_init(&qp->sq.lock);
	spin_lock_init(&qp->rq.lock);

	if (init_attr->rwq_ind_tbl) {
		if (!udata)
			return -ENOSYS;

		err = create_rss_raw_qp_tir(dev, qp, pd, init_attr, udata);
		return err;
	}

	if (init_attr->create_flags & IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK) {
		if (!MLX5_CAP_GEN(mdev, block_lb_mc)) {
			mlx5_ib_dbg(dev, "block multicast loopback isn't supported\n");
			return -EINVAL;
		} else {
			qp->flags |= MLX5_IB_QP_BLOCK_MULTICAST_LOOPBACK;
		}
	}

	if (init_attr->create_flags &
			(IB_QP_CREATE_CROSS_CHANNEL |
			 IB_QP_CREATE_MANAGED_SEND |
			 IB_QP_CREATE_MANAGED_RECV)) {
		if (!MLX5_CAP_GEN(mdev, cd)) {
			mlx5_ib_dbg(dev, "cross-channel isn't supported\n");
			return -EINVAL;
		}
		if (init_attr->create_flags & IB_QP_CREATE_CROSS_CHANNEL)
			qp->flags |= MLX5_IB_QP_CROSS_CHANNEL;
		if (init_attr->create_flags & IB_QP_CREATE_MANAGED_SEND)
			qp->flags |= MLX5_IB_QP_MANAGED_SEND;
		if (init_attr->create_flags & IB_QP_CREATE_MANAGED_RECV)
			qp->flags |= MLX5_IB_QP_MANAGED_RECV;
	}

	if (init_attr->qp_type == IB_QPT_UD &&
	    (init_attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO))
		if (!MLX5_CAP_GEN(mdev, ipoib_ipoib_offloads)) {
			mlx5_ib_dbg(dev, "ipoib UD lso qp isn't supported\n");
			return -EOPNOTSUPP;
		}

	if (init_attr->create_flags & IB_QP_CREATE_SCATTER_FCS) {
		if (init_attr->qp_type != IB_QPT_RAW_PACKET) {
			mlx5_ib_dbg(dev, "Scatter FCS is supported only for Raw Packet QPs");
			return -EOPNOTSUPP;
		}
		if (!MLX5_CAP_GEN(dev->mdev, eth_net_offloads) ||
		    !MLX5_CAP_ETH(dev->mdev, scatter_fcs)) {
			mlx5_ib_dbg(dev, "Scatter FCS isn't supported\n");
			return -EOPNOTSUPP;
		}
		qp->flags |= MLX5_IB_QP_CAP_SCATTER_FCS;
	}

	if (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR)
		qp->sq_signal_bits = MLX5_WQE_CTRL_CQ_UPDATE;

	if (pd && pd->uobject) {
		if (ib_copy_from_udata(&ucmd, udata, sizeof(ucmd))) {
			mlx5_ib_dbg(dev, "copy failed\n");
			return -EFAULT;
		}

		err = get_qp_user_index(to_mucontext(pd->uobject->context),
					&ucmd, udata->inlen, &uidx);
		if (err)
			return err;

		qp->wq_sig = !!(ucmd.flags & MLX5_QP_FLAG_SIGNATURE);
		qp->scat_cqe = !!(ucmd.flags & MLX5_QP_FLAG_SCATTER_CQE);
	} else {
		qp->wq_sig = !!wq_signature;
	}

	qp->has_rq = qp_has_rq(init_attr);
	err = set_rq_size(dev, &init_attr->cap, qp->has_rq,
			  qp, (pd && pd->uobject) ? &ucmd : NULL);
	if (err) {
		mlx5_ib_dbg(dev, "err %d\n", err);
		return err;
	}

	if (pd) {
		if (pd->uobject) {
			__u32 max_wqes =
				1 << MLX5_CAP_GEN(mdev, log_max_qp_sz);
			mlx5_ib_dbg(dev, "requested sq_wqe_count (%d)\n", ucmd.sq_wqe_count);
			if (ucmd.rq_wqe_shift != qp->rq.wqe_shift ||
			    ucmd.rq_wqe_count != qp->rq.wqe_cnt) {
				mlx5_ib_dbg(dev, "invalid rq params\n");
				return -EINVAL;
			}
			if (ucmd.sq_wqe_count > max_wqes) {
				mlx5_ib_dbg(dev, "requested sq_wqe_count (%d) > max allowed (%d)\n",
					    ucmd.sq_wqe_count, max_wqes);
				return -EINVAL;
			}
			if (init_attr->create_flags &
			    mlx5_ib_create_qp_sqpn_qp1()) {
				mlx5_ib_dbg(dev, "user-space is not allowed to create UD QPs spoofing as QP1\n");
				return -EINVAL;
			}
			err = create_user_qp(dev, pd, qp, udata, init_attr, &in,
					     &resp, &inlen, base);
			if (err)
				mlx5_ib_dbg(dev, "err %d\n", err);
		} else {
			err = create_kernel_qp(dev, init_attr, qp, &in, &inlen,
					       base);
			if (err)
				mlx5_ib_dbg(dev, "err %d\n", err);
		}

		if (err)
			return err;
	} else {
		in = mlx5_vzalloc(inlen);
		if (!in)
			return -ENOMEM;

		qp->create_type = MLX5_QP_EMPTY;
	}

	if (is_sqp(init_attr->qp_type))
		qp->port = init_attr->port_num;

	qpc = MLX5_ADDR_OF(create_qp_in, in, qpc);

	MLX5_SET(qpc, qpc, st, to_mlx5_st(init_attr->qp_type));
	MLX5_SET(qpc, qpc, pm_state, MLX5_QP_PM_MIGRATED);

	if (init_attr->qp_type != MLX5_IB_QPT_REG_UMR)
		MLX5_SET(qpc, qpc, pd, to_mpd(pd ? pd : devr->p0)->pdn);
	else
		MLX5_SET(qpc, qpc, latency_sensitive, 1);


	if (qp->wq_sig)
		MLX5_SET(qpc, qpc, wq_signature, 1);

	if (qp->flags & MLX5_IB_QP_BLOCK_MULTICAST_LOOPBACK)
		MLX5_SET(qpc, qpc, block_lb_mc, 1);

	if (qp->flags & MLX5_IB_QP_CROSS_CHANNEL)
		MLX5_SET(qpc, qpc, cd_master, 1);
	if (qp->flags & MLX5_IB_QP_MANAGED_SEND)
		MLX5_SET(qpc, qpc, cd_slave_send, 1);
	if (qp->flags & MLX5_IB_QP_MANAGED_RECV)
		MLX5_SET(qpc, qpc, cd_slave_receive, 1);

	if (qp->scat_cqe && is_connected(init_attr->qp_type)) {
		int rcqe_sz;
		int scqe_sz;

		rcqe_sz = mlx5_ib_get_cqe_size(dev, init_attr->recv_cq);
		scqe_sz = mlx5_ib_get_cqe_size(dev, init_attr->send_cq);

		if (rcqe_sz == 128)
			MLX5_SET(qpc, qpc, cs_res, MLX5_RES_SCAT_DATA64_CQE);
		else
			MLX5_SET(qpc, qpc, cs_res, MLX5_RES_SCAT_DATA32_CQE);

		if (init_attr->sq_sig_type == IB_SIGNAL_ALL_WR) {
			if (scqe_sz == 128)
				MLX5_SET(qpc, qpc, cs_req, MLX5_REQ_SCAT_DATA64_CQE);
			else
				MLX5_SET(qpc, qpc, cs_req, MLX5_REQ_SCAT_DATA32_CQE);
		}
	}

	if (qp->rq.wqe_cnt) {
		MLX5_SET(qpc, qpc, log_rq_stride, qp->rq.wqe_shift - 4);
		MLX5_SET(qpc, qpc, log_rq_size, ilog2(qp->rq.wqe_cnt));
	}

	MLX5_SET(qpc, qpc, rq_type, get_rx_type(qp, init_attr));

	if (qp->sq.wqe_cnt)
		MLX5_SET(qpc, qpc, log_sq_size, ilog2(qp->sq.wqe_cnt));
	else
		MLX5_SET(qpc, qpc, no_sq, 1);

	/* Set default resources */
	switch (init_attr->qp_type) {
	case IB_QPT_XRC_TGT:
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(devr->c0)->mcq.cqn);
		MLX5_SET(qpc, qpc, cqn_snd, to_mcq(devr->c0)->mcq.cqn);
		MLX5_SET(qpc, qpc, srqn_rmpn, to_msrq(devr->s0)->msrq.srqn);
		MLX5_SET(qpc, qpc, xrcd, to_mxrcd(init_attr->xrcd)->xrcdn);
		break;
	case IB_QPT_XRC_INI:
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(devr->c0)->mcq.cqn);
		MLX5_SET(qpc, qpc, xrcd, to_mxrcd(devr->x1)->xrcdn);
		MLX5_SET(qpc, qpc, srqn_rmpn, to_msrq(devr->s0)->msrq.srqn);
		break;
	default:
		if (init_attr->srq) {
			MLX5_SET(qpc, qpc, xrcd, to_mxrcd(devr->x0)->xrcdn);
			MLX5_SET(qpc, qpc, srqn_rmpn, to_msrq(init_attr->srq)->msrq.srqn);
		} else {
			MLX5_SET(qpc, qpc, xrcd, to_mxrcd(devr->x1)->xrcdn);
			MLX5_SET(qpc, qpc, srqn_rmpn, to_msrq(devr->s1)->msrq.srqn);
		}
	}

	if (init_attr->send_cq)
		MLX5_SET(qpc, qpc, cqn_snd, to_mcq(init_attr->send_cq)->mcq.cqn);

	if (init_attr->recv_cq)
		MLX5_SET(qpc, qpc, cqn_rcv, to_mcq(init_attr->recv_cq)->mcq.cqn);

	MLX5_SET64(qpc, qpc, dbr_addr, qp->db.dma);

	/* 0xffffff means we ask to work with cqe version 0 */
	if (MLX5_CAP_GEN(mdev, cqe_version) == MLX5_CQE_VERSION_V1)
		MLX5_SET(qpc, qpc, user_index, uidx);

	/* we use IB_QP_CREATE_IPOIB_UD_LSO to indicates ipoib qp */
	if (init_attr->qp_type == IB_QPT_UD &&
	    (init_attr->create_flags & IB_QP_CREATE_IPOIB_UD_LSO)) {
		MLX5_SET(qpc, qpc, ulp_stateless_offload_mode, 1);
		qp->flags |= MLX5_IB_QP_LSO;
	}

	if (init_attr->qp_type == IB_QPT_RAW_PACKET) {
		qp->raw_packet_qp.sq.ubuffer.buf_addr = ucmd.sq_buf_addr;
		raw_packet_qp_copy_info(qp, &qp->raw_packet_qp);
		err = create_raw_packet_qp(dev, qp, in, pd);
	} else {
		err = mlx5_core_create_qp(dev->mdev, &base->mqp, in, inlen);
	}

	if (err) {
		mlx5_ib_dbg(dev, "create qp failed\n");
		goto err_create;
	}

	kvfree(in);

	base->container_mibqp = qp;
	base->mqp.event = mlx5_ib_qp_event;

	get_cqs(init_attr->qp_type, init_attr->send_cq, init_attr->recv_cq,
		&send_cq, &recv_cq);
	spin_lock_irqsave(&dev->reset_flow_resource_lock, flags);
	mlx5_ib_lock_cqs(send_cq, recv_cq);
	/* Maintain device to QPs access, needed for further handling via reset
	 * flow
	 */
	list_add_tail(&qp->qps_list, &dev->qp_list);
	/* Maintain CQ to QPs access, needed for further handling via reset flow
	 */
	if (send_cq)
		list_add_tail(&qp->cq_send_list, &send_cq->list_send_qp);
	if (recv_cq)
		list_add_tail(&qp->cq_recv_list, &recv_cq->list_recv_qp);
	mlx5_ib_unlock_cqs(send_cq, recv_cq);
	spin_unlock_irqrestore(&dev->reset_flow_resource_lock, flags);

	return 0;

err_create:
	if (qp->create_type == MLX5_QP_USER)
		destroy_qp_user(pd, qp, base);
	else if (qp->create_type == MLX5_QP_KERNEL)
		destroy_qp_kernel(dev, qp);

	kvfree(in);
	return err;
}