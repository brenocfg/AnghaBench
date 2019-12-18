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
typedef  int uint32_t ;
struct mlx5_wqe_eth_seg {int inline_hdr_start; int /*<<< orphan*/  inline_hdr_sz; } ;
struct mlx5_sg_copy_ptr {int index; int offset; } ;
struct ibv_send_wr {int num_sge; TYPE_1__* sg_list; } ;
struct ibv_qp {int /*<<< orphan*/  context; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dbg_fp; } ;
struct TYPE_3__ {int length; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_DBG_QP_SEND ; 
 int MLX5_ETH_L2_INLINE_HEADER_SIZE ; 
 int /*<<< orphan*/  htobe16 (int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (int,void*,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__* to_mctx (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int copy_eth_inline_headers(struct ibv_qp *ibqp,
					  struct ibv_send_wr *wr,
					  struct mlx5_wqe_eth_seg *eseg,
					  struct mlx5_sg_copy_ptr *sg_copy_ptr)
{
	uint32_t inl_hdr_size = MLX5_ETH_L2_INLINE_HEADER_SIZE;
	int inl_hdr_copy_size = 0;
	int j = 0;
	FILE *fp = to_mctx(ibqp->context)->dbg_fp;

	if (unlikely(wr->num_sge < 1)) {
		mlx5_dbg(fp, MLX5_DBG_QP_SEND, "illegal num_sge: %d, minimum is 1\n",
			 wr->num_sge);
		return EINVAL;
	}

	if (likely(wr->sg_list[0].length >= MLX5_ETH_L2_INLINE_HEADER_SIZE)) {
		inl_hdr_copy_size = MLX5_ETH_L2_INLINE_HEADER_SIZE;
		memcpy(eseg->inline_hdr_start,
		       (void *)(uintptr_t)wr->sg_list[0].addr,
		       inl_hdr_copy_size);
	} else {
		for (j = 0; j < wr->num_sge && inl_hdr_size > 0; ++j) {
			inl_hdr_copy_size = min(wr->sg_list[j].length,
						inl_hdr_size);
			memcpy(eseg->inline_hdr_start +
			       (MLX5_ETH_L2_INLINE_HEADER_SIZE - inl_hdr_size),
			       (void *)(uintptr_t)wr->sg_list[j].addr,
			       inl_hdr_copy_size);
			inl_hdr_size -= inl_hdr_copy_size;
		}
		if (unlikely(inl_hdr_size)) {
			mlx5_dbg(fp, MLX5_DBG_QP_SEND, "Ethernet headers < 16 bytes\n");
			return EINVAL;
		}
		--j;
	}


	eseg->inline_hdr_sz = htobe16(MLX5_ETH_L2_INLINE_HEADER_SIZE);

	/* If we copied all the sge into the inline-headers, then we need to
	 * start copying from the next sge into the data-segment.
	 */
	if (unlikely(wr->sg_list[j].length == inl_hdr_copy_size)) {
		++j;
		inl_hdr_copy_size = 0;
	}

	sg_copy_ptr->index = j;
	sg_copy_ptr->offset = inl_hdr_copy_size;

	return 0;
}