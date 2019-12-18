#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx5_resize_cq_resp {uintptr_t buf_addr; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  cqe_size; } ;
struct mlx5_resize_cq {uintptr_t buf_addr; int /*<<< orphan*/  ibv_resp; int /*<<< orphan*/  ibv_cmd; int /*<<< orphan*/  cqe_size; } ;
struct TYPE_4__ {int cqe; } ;
struct TYPE_5__ {scalar_t__ buf; } ;
struct mlx5_cq {int active_cqes; int resize_cqes; int /*<<< orphan*/  lock; TYPE_2__* resize_buf; TYPE_1__ ibv_cq; TYPE_2__* active_buf; int /*<<< orphan*/  resize_cqe_sz; int /*<<< orphan*/  cqe_sz; TYPE_2__ buf_a; TYPE_2__ buf_b; } ;
struct mlx5_context {int dummy; } ;
struct ibv_cq {int cqe; int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 long long INT_MAX ; 
 int align_queue_size (int) ; 
 int errno ; 
 int ibv_cmd_resize_cq (struct ibv_cq*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct mlx5_resize_cq_resp*,int /*<<< orphan*/ ,int) ; 
 int mlx5_alloc_cq_buf (struct mlx5_context*,struct mlx5_cq*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cq_resize_copy_cqes (struct mlx5_cq*) ; 
 int /*<<< orphan*/  mlx5_free_cq_buf (struct mlx5_context*,TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx5_cq* to_mcq (struct ibv_cq*) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 

int mlx5_resize_cq(struct ibv_cq *ibcq, int cqe)
{
	struct mlx5_cq *cq = to_mcq(ibcq);
	struct mlx5_resize_cq_resp resp;
	struct mlx5_resize_cq cmd;
	struct mlx5_context *mctx = to_mctx(ibcq->context);
	int err;

	if (cqe < 0) {
		errno = EINVAL;
		return errno;
	}

	memset(&cmd, 0, sizeof(cmd));
	memset(&resp, 0, sizeof(resp));

	if (((long long)cqe * 64) > INT_MAX)
		return EINVAL;

	mlx5_spin_lock(&cq->lock);
	cq->active_cqes = cq->ibv_cq.cqe;
	if (cq->active_buf == &cq->buf_a)
		cq->resize_buf = &cq->buf_b;
	else
		cq->resize_buf = &cq->buf_a;

	cqe = align_queue_size(cqe + 1);
	if (cqe == ibcq->cqe + 1) {
		cq->resize_buf = NULL;
		err = 0;
		goto out;
	}

	/* currently we don't change cqe size */
	cq->resize_cqe_sz = cq->cqe_sz;
	cq->resize_cqes = cqe;
	err = mlx5_alloc_cq_buf(mctx, cq, cq->resize_buf, cq->resize_cqes, cq->resize_cqe_sz);
	if (err) {
		cq->resize_buf = NULL;
		errno = ENOMEM;
		goto out;
	}

	cmd.buf_addr = (uintptr_t)cq->resize_buf->buf;
	cmd.cqe_size = cq->resize_cqe_sz;

	err = ibv_cmd_resize_cq(ibcq, cqe - 1, &cmd.ibv_cmd, sizeof(cmd),
				&resp.ibv_resp, sizeof(resp));
	if (err)
		goto out_buf;

	mlx5_cq_resize_copy_cqes(cq);
	mlx5_free_cq_buf(mctx, cq->active_buf);
	cq->active_buf = cq->resize_buf;
	cq->ibv_cq.cqe = cqe - 1;
	mlx5_spin_unlock(&cq->lock);
	cq->resize_buf = NULL;
	return 0;

out_buf:
	mlx5_free_cq_buf(mctx, cq->resize_buf);
	cq->resize_buf = NULL;

out:
	mlx5_spin_unlock(&cq->lock);
	return err;
}