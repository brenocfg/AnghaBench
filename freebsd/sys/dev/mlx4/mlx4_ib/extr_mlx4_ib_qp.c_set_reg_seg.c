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
struct mlx4_wqe_fmr_seg {scalar_t__* reserved; void* page_size; scalar_t__ offset; void* reg_len; void* start_addr; void* buf_list; void* mem_key; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  page_size; int /*<<< orphan*/  length; int /*<<< orphan*/  iova; } ;
struct mlx4_ib_mr {TYPE_1__ ibmr; int /*<<< orphan*/  page_map; } ;
struct ib_reg_wr {int /*<<< orphan*/  key; int /*<<< orphan*/  access; int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 int /*<<< orphan*/  convert_access (int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_mr* to_mmr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_reg_seg(struct mlx4_wqe_fmr_seg *fseg,
			struct ib_reg_wr *wr)
{
	struct mlx4_ib_mr *mr = to_mmr(wr->mr);

	fseg->flags		= convert_access(wr->access);
	fseg->mem_key		= cpu_to_be32(wr->key);
	fseg->buf_list		= cpu_to_be64(mr->page_map);
	fseg->start_addr	= cpu_to_be64(mr->ibmr.iova);
	fseg->reg_len		= cpu_to_be64(mr->ibmr.length);
	fseg->offset		= 0; /* XXX -- is this just for ZBVA? */
	fseg->page_size		= cpu_to_be32(ilog2(mr->ibmr.page_size));
	fseg->reserved[0]	= 0;
	fseg->reserved[1]	= 0;
}