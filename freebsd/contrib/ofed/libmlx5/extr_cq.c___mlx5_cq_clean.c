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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mlx5_srq {int dummy; } ;
struct mlx5_cqe64 {int op_own; } ;
struct TYPE_3__ {int cqe; int /*<<< orphan*/  context; } ;
struct mlx5_cq {int flags; int cons_index; int cqe_sz; TYPE_1__ ibv_cq; } ;
struct TYPE_4__ {int cqe_version; } ;

/* Variables and functions */
 int MLX5_CQE_OWNER_MASK ; 
 int MLX5_CQ_FLAGS_DV_OWNED ; 
 scalar_t__ free_res_cqe (struct mlx5_cqe64*,int,struct mlx5_srq*,int) ; 
 void* get_cqe (struct mlx5_cq*,int) ; 
 scalar_t__ get_sw_cqe (struct mlx5_cq*,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 TYPE_2__* to_mctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 
 int /*<<< orphan*/  update_cons_index (struct mlx5_cq*) ; 

void __mlx5_cq_clean(struct mlx5_cq *cq, uint32_t rsn, struct mlx5_srq *srq)
{
	uint32_t prod_index;
	int nfreed = 0;
	struct mlx5_cqe64 *cqe64, *dest64;
	void *cqe, *dest;
	uint8_t owner_bit;
	int cqe_version;

	if (!cq || cq->flags & MLX5_CQ_FLAGS_DV_OWNED)
		return;

	/*
	 * First we need to find the current producer index, so we
	 * know where to start cleaning from.  It doesn't matter if HW
	 * adds new entries after this loop -- the QP we're worried
	 * about is already in RESET, so the new entries won't come
	 * from our QP and therefore don't need to be checked.
	 */
	for (prod_index = cq->cons_index; get_sw_cqe(cq, prod_index); ++prod_index)
		if (prod_index == cq->cons_index + cq->ibv_cq.cqe)
			break;

	/*
	 * Now sweep backwards through the CQ, removing CQ entries
	 * that match our QP by copying older entries on top of them.
	 */
	cqe_version = (to_mctx(cq->ibv_cq.context))->cqe_version;
	while ((int) --prod_index - (int) cq->cons_index >= 0) {
		cqe = get_cqe(cq, prod_index & cq->ibv_cq.cqe);
		cqe64 = (cq->cqe_sz == 64) ? cqe : cqe + 64;
		if (free_res_cqe(cqe64, rsn, srq, cqe_version)) {
			++nfreed;
		} else if (nfreed) {
			dest = get_cqe(cq, (prod_index + nfreed) & cq->ibv_cq.cqe);
			dest64 = (cq->cqe_sz == 64) ? dest : dest + 64;
			owner_bit = dest64->op_own & MLX5_CQE_OWNER_MASK;
			memcpy(dest, cqe, cq->cqe_sz);
			dest64->op_own = owner_bit |
				(dest64->op_own & ~MLX5_CQE_OWNER_MASK);
		}
	}

	if (nfreed) {
		cq->cons_index += nfreed;
		/*
		 * Make sure update of buffer contents is done before
		 * updating consumer index.
		 */
		udma_to_device_barrier();
		update_cons_index(cq);
	}
}