#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_stride_block_entry {void* stride; void* va; void* key; void* bcount; } ;
struct mlx5_stride_block_ctrl_seg {void* num_entries; void* repeat_count; void* op; void* bcount_per_cycle; } ;
struct mlx5_klm {void* va; void* key; void* bcount; } ;
struct TYPE_14__ {void* qend; } ;
struct mlx5_ib_qp {TYPE_7__ sq; } ;
struct mlx5_bsf {int dummy; } ;
struct TYPE_9__ {TYPE_1__* sg_list; } ;
struct ib_sig_handover_wr {TYPE_3__* prot; TYPE_2__ wr; struct ib_mr* sig_mr; struct ib_sig_attrs* sig_attrs; } ;
struct TYPE_11__ {int pi_interval; } ;
struct TYPE_12__ {TYPE_4__ dif; } ;
struct TYPE_13__ {int /*<<< orphan*/  sig_type; TYPE_5__ sig; } ;
struct ib_sig_attrs {TYPE_6__ mem; } ;
struct ib_mr {int dummy; } ;
struct TYPE_10__ {int lkey; scalar_t__ addr; int length; } ;
struct TYPE_8__ {int length; int lkey; scalar_t__ addr; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int EINVAL ; 
 int MLX5_STRIDE_BLOCK_OP ; 
 void* cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 void* mlx5_get_send_wqe (struct mlx5_ib_qp*,int /*<<< orphan*/ ) ; 
 int mlx5_set_bsf (struct ib_mr*,struct ib_sig_attrs*,struct mlx5_bsf*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int prot_field_size (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int set_sig_data_segment(struct ib_sig_handover_wr *wr,
				struct mlx5_ib_qp *qp, void **seg, int *size)
{
	struct ib_sig_attrs *sig_attrs = wr->sig_attrs;
	struct ib_mr *sig_mr = wr->sig_mr;
	struct mlx5_bsf *bsf;
	u32 data_len = wr->wr.sg_list->length;
	u32 data_key = wr->wr.sg_list->lkey;
	u64 data_va = wr->wr.sg_list->addr;
	int ret;
	int wqe_size;

	if (!wr->prot ||
	    (data_key == wr->prot->lkey &&
	     data_va == wr->prot->addr &&
	     data_len == wr->prot->length)) {
		/**
		 * Source domain doesn't contain signature information
		 * or data and protection are interleaved in memory.
		 * So need construct:
		 *                  ------------------
		 *                 |     data_klm     |
		 *                  ------------------
		 *                 |       BSF        |
		 *                  ------------------
		 **/
		struct mlx5_klm *data_klm = *seg;

		data_klm->bcount = cpu_to_be32(data_len);
		data_klm->key = cpu_to_be32(data_key);
		data_klm->va = cpu_to_be64(data_va);
		wqe_size = ALIGN(sizeof(*data_klm), 64);
	} else {
		/**
		 * Source domain contains signature information
		 * So need construct a strided block format:
		 *               ---------------------------
		 *              |     stride_block_ctrl     |
		 *               ---------------------------
		 *              |          data_klm         |
		 *               ---------------------------
		 *              |          prot_klm         |
		 *               ---------------------------
		 *              |             BSF           |
		 *               ---------------------------
		 **/
		struct mlx5_stride_block_ctrl_seg *sblock_ctrl;
		struct mlx5_stride_block_entry *data_sentry;
		struct mlx5_stride_block_entry *prot_sentry;
		u32 prot_key = wr->prot->lkey;
		u64 prot_va = wr->prot->addr;
		u16 block_size = sig_attrs->mem.sig.dif.pi_interval;
		int prot_size;

		sblock_ctrl = *seg;
		data_sentry = (void *)sblock_ctrl + sizeof(*sblock_ctrl);
		prot_sentry = (void *)data_sentry + sizeof(*data_sentry);

		prot_size = prot_field_size(sig_attrs->mem.sig_type);
		if (!prot_size) {
			pr_err("Bad block size given: %u\n", block_size);
			return -EINVAL;
		}
		sblock_ctrl->bcount_per_cycle = cpu_to_be32(block_size +
							    prot_size);
		sblock_ctrl->op = cpu_to_be32(MLX5_STRIDE_BLOCK_OP);
		sblock_ctrl->repeat_count = cpu_to_be32(data_len / block_size);
		sblock_ctrl->num_entries = cpu_to_be16(2);

		data_sentry->bcount = cpu_to_be16(block_size);
		data_sentry->key = cpu_to_be32(data_key);
		data_sentry->va = cpu_to_be64(data_va);
		data_sentry->stride = cpu_to_be16(block_size);

		prot_sentry->bcount = cpu_to_be16(prot_size);
		prot_sentry->key = cpu_to_be32(prot_key);
		prot_sentry->va = cpu_to_be64(prot_va);
		prot_sentry->stride = cpu_to_be16(prot_size);

		wqe_size = ALIGN(sizeof(*sblock_ctrl) + sizeof(*data_sentry) +
				 sizeof(*prot_sentry), 64);
	}

	*seg += wqe_size;
	*size += wqe_size / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);

	bsf = *seg;
	ret = mlx5_set_bsf(sig_mr, sig_attrs, bsf, data_len);
	if (ret)
		return -EINVAL;

	*seg += sizeof(*bsf);
	*size += sizeof(*bsf) / 16;
	if (unlikely((*seg == qp->sq.qend)))
		*seg = mlx5_get_send_wqe(qp, 0);

	return 0;
}