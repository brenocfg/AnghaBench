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
struct TYPE_3__ {int srq_num; } ;
struct mlx4_srq {TYPE_1__ verbs_srq; scalar_t__ ext_srq; } ;
struct mlx4_cqe {int owner_sr_opcode; int /*<<< orphan*/  wqe_index; int /*<<< orphan*/  vlan_my_qpn; int /*<<< orphan*/  g_mlpath_rqpn; } ;
struct TYPE_4__ {int cqe; } ;
struct mlx4_cq {int cqe_size; int cons_index; TYPE_2__ ibv_cq; } ;

/* Variables and functions */
 int MLX4_CQE_IS_SEND_MASK ; 
 int MLX4_CQE_OWNER_MASK ; 
 int MLX4_CQE_QPN_MASK ; 
 int /*<<< orphan*/  be16toh (int /*<<< orphan*/ ) ; 
 int be32toh (int /*<<< orphan*/ ) ; 
 struct mlx4_cqe* get_cqe (struct mlx4_cq*,int) ; 
 scalar_t__ get_sw_cqe (struct mlx4_cq*,int) ; 
 int /*<<< orphan*/  memcpy (struct mlx4_cqe*,struct mlx4_cqe*,int) ; 
 int /*<<< orphan*/  mlx4_free_srq_wqe (struct mlx4_srq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_update_cons_index (struct mlx4_cq*) ; 
 int /*<<< orphan*/  udma_to_device_barrier () ; 

void __mlx4_cq_clean(struct mlx4_cq *cq, uint32_t qpn, struct mlx4_srq *srq)
{
	struct mlx4_cqe *cqe, *dest;
	uint32_t prod_index;
	uint8_t owner_bit;
	int nfreed = 0;
	int cqe_inc = cq->cqe_size == 64 ? 1 : 0;

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
	while ((int) --prod_index - (int) cq->cons_index >= 0) {
		cqe = get_cqe(cq, prod_index & cq->ibv_cq.cqe);
		cqe += cqe_inc;
		if (srq && srq->ext_srq &&
		    (be32toh(cqe->g_mlpath_rqpn) & MLX4_CQE_QPN_MASK) == srq->verbs_srq.srq_num &&
		    !(cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK)) {
			mlx4_free_srq_wqe(srq, be16toh(cqe->wqe_index));
			++nfreed;
		} else if ((be32toh(cqe->vlan_my_qpn) & MLX4_CQE_QPN_MASK) == qpn) {
			if (srq && !(cqe->owner_sr_opcode & MLX4_CQE_IS_SEND_MASK))
				mlx4_free_srq_wqe(srq, be16toh(cqe->wqe_index));
			++nfreed;
		} else if (nfreed) {
			dest = get_cqe(cq, (prod_index + nfreed) & cq->ibv_cq.cqe);
			dest += cqe_inc;
			owner_bit = dest->owner_sr_opcode & MLX4_CQE_OWNER_MASK;
			memcpy(dest, cqe, sizeof *cqe);
			dest->owner_sr_opcode = owner_bit |
				(dest->owner_sr_opcode & ~MLX4_CQE_OWNER_MASK);
		}
	}

	if (nfreed) {
		cq->cons_index += nfreed;
		/*
		 * Make sure update of buffer contents is done before
		 * updating consumer index.
		 */
		udma_to_device_barrier();
		mlx4_update_cons_index(cq);
	}
}