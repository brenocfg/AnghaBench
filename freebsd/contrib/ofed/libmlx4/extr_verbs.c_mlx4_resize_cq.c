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
struct mlx4_resize_cq {uintptr_t buf_addr; int /*<<< orphan*/  ibv_cmd; } ;
struct mlx4_buf {scalar_t__ buf; } ;
struct mlx4_cq {int /*<<< orphan*/  lock; struct mlx4_buf buf; int /*<<< orphan*/  cqe_size; } ;
struct ibv_resize_cq_resp {int dummy; } ;
struct ibv_cq {int cqe; TYPE_1__* context; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 int align_queue_size (int) ; 
 int ibv_cmd_resize_cq (struct ibv_cq*,int,int /*<<< orphan*/ *,int,struct ibv_resize_cq_resp*,int) ; 
 int mlx4_alloc_cq_buf (int /*<<< orphan*/ ,struct mlx4_buf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cq_resize_copy_cqes (struct mlx4_cq*,scalar_t__,int) ; 
 int /*<<< orphan*/  mlx4_free_buf (struct mlx4_buf*) ; 
 int mlx4_get_outstanding_cqes (struct mlx4_cq*) ; 
 int /*<<< orphan*/  mlx4_update_cons_index (struct mlx4_cq*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_cq* to_mcq (struct ibv_cq*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 

int mlx4_resize_cq(struct ibv_cq *ibcq, int cqe)
{
	struct mlx4_cq *cq = to_mcq(ibcq);
	struct mlx4_resize_cq cmd;
	struct ibv_resize_cq_resp resp;
	struct mlx4_buf buf;
	int old_cqe, outst_cqe, ret;

	/* Sanity check CQ size before proceeding */
	if (cqe > 0x3fffff)
		return EINVAL;

	pthread_spin_lock(&cq->lock);

	cqe = align_queue_size(cqe + 1);
	if (cqe == ibcq->cqe + 1) {
		ret = 0;
		goto out;
	}

	/* Can't be smaller then the number of outstanding CQEs */
	outst_cqe = mlx4_get_outstanding_cqes(cq);
	if (cqe < outst_cqe + 1) {
		ret = EINVAL;
		goto out;
	}

	ret = mlx4_alloc_cq_buf(to_mdev(ibcq->context->device), &buf, cqe, cq->cqe_size);
	if (ret)
		goto out;

	old_cqe = ibcq->cqe;
	cmd.buf_addr = (uintptr_t) buf.buf;

	ret = ibv_cmd_resize_cq(ibcq, cqe - 1, &cmd.ibv_cmd, sizeof cmd,
				&resp, sizeof resp);
	if (ret) {
		mlx4_free_buf(&buf);
		goto out;
	}

	mlx4_cq_resize_copy_cqes(cq, buf.buf, old_cqe);

	mlx4_free_buf(&cq->buf);
	cq->buf = buf;
	mlx4_update_cons_index(cq);

out:
	pthread_spin_unlock(&cq->lock);
	return ret;
}