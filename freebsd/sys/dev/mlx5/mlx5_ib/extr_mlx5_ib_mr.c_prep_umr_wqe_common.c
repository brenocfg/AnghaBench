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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_umr_wr {int npages; int page_shift; int /*<<< orphan*/  mkey; } ;
struct TYPE_4__ {TYPE_1__* pd; } ;
struct mlx5_ib_dev {TYPE_2__ umrc; } ;
struct ib_sge {int /*<<< orphan*/  lkey; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct ib_send_wr {int num_sge; int /*<<< orphan*/  opcode; struct ib_sge* sg_list; int /*<<< orphan*/ * next; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_3__ {int /*<<< orphan*/  local_dma_lkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int,int) ; 
 int /*<<< orphan*/  MLX5_IB_WR_UMR ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_umr_wr* umr_wr (struct ib_send_wr*) ; 

__attribute__((used)) static void prep_umr_wqe_common(struct ib_pd *pd, struct ib_send_wr *wr,
				struct ib_sge *sg, u64 dma, int n, u32 key,
				int page_shift)
{
	struct mlx5_ib_dev *dev = to_mdev(pd->device);
	struct mlx5_umr_wr *umrwr = umr_wr(wr);

	sg->addr = dma;
	sg->length = ALIGN(sizeof(u64) * n, 64);
	sg->lkey = dev->umrc.pd->local_dma_lkey;

	wr->next = NULL;
	wr->sg_list = sg;
	if (n)
		wr->num_sge = 1;
	else
		wr->num_sge = 0;

	wr->opcode = MLX5_IB_WR_UMR;

	umrwr->npages = n;
	umrwr->page_shift = page_shift;
	umrwr->mkey = key;
}