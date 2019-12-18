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
typedef  scalar_t__ uint64_t ;
struct mlx5_wqe_eth_seg {void* inline_hdr_start; void* inline_hdr_sz; void* mss; } ;
struct mlx5_qp {scalar_t__ max_tso_header; TYPE_1__* ibv_qp; } ;
struct TYPE_5__ {scalar_t__ hdr_sz; scalar_t__ mss; void* hdr; } ;
struct ibv_send_wr {TYPE_2__ tso; } ;
struct TYPE_6__ {int /*<<< orphan*/ * dbg_fp; } ;
struct TYPE_4__ {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_DBG_QP_SEND ; 
 scalar_t__ MLX5_ETH_L2_MIN_HEADER_SIZE ; 
 int align (scalar_t__,int) ; 
 void* htobe16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 void* mlx5_get_send_wqe (struct mlx5_qp*,int /*<<< orphan*/ ) ; 
 TYPE_3__* to_mctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int set_tso_eth_seg(void **seg, struct ibv_send_wr *wr,
				   void *qend, struct mlx5_qp *qp, int *size)
{
	struct mlx5_wqe_eth_seg *eseg = *seg;
	int size_of_inl_hdr_start = sizeof(eseg->inline_hdr_start);
	uint64_t left, left_len, copy_sz;
	void *pdata = wr->tso.hdr;
	FILE *fp = to_mctx(qp->ibv_qp->context)->dbg_fp;

	if (unlikely(wr->tso.hdr_sz < MLX5_ETH_L2_MIN_HEADER_SIZE ||
		     wr->tso.hdr_sz > qp->max_tso_header)) {
		mlx5_dbg(fp, MLX5_DBG_QP_SEND,
			 "TSO header size should be at least %d and at most %d\n",
			 MLX5_ETH_L2_MIN_HEADER_SIZE,
			 qp->max_tso_header);
		return EINVAL;
	}

	left = wr->tso.hdr_sz;
	eseg->mss = htobe16(wr->tso.mss);
	eseg->inline_hdr_sz = htobe16(wr->tso.hdr_sz);

	/* Check if there is space till the end of queue, if yes,
	 * copy all in one shot, otherwise copy till the end of queue,
	 * rollback and then copy the left
	 */
	left_len = qend - (void *)eseg->inline_hdr_start;
	copy_sz = min(left_len, left);

	memcpy(eseg->inline_hdr_start, pdata, copy_sz);

	/* The -1 is because there are already 16 bytes included in
	 * eseg->inline_hdr[16]
	 */
	*seg += align(copy_sz - size_of_inl_hdr_start, 16) - 16;
	*size += align(copy_sz - size_of_inl_hdr_start, 16) / 16 - 1;

	/* The last wqe in the queue */
	if (unlikely(copy_sz < left)) {
		*seg = mlx5_get_send_wqe(qp, 0);
		left -= copy_sz;
		pdata += copy_sz;
		memcpy(*seg, pdata, left);
		*seg += align(left, 16);
		*size += align(left, 16) / 16;
	}

	return 0;
}