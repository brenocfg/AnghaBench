#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct mlx5_wqe_atomic_seg {void* swap_add; void* compare; } ;
typedef  enum ibv_wr_opcode { ____Placeholder_ibv_wr_opcode } ibv_wr_opcode ;

/* Variables and functions */
 int IBV_WR_ATOMIC_CMP_AND_SWP ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_atomic_seg(struct mlx5_wqe_atomic_seg *aseg,
			   enum ibv_wr_opcode   opcode,
			   uint64_t swap,
			   uint64_t compare_add)
{
	if (opcode == IBV_WR_ATOMIC_CMP_AND_SWP) {
		aseg->swap_add = htobe64(swap);
		aseg->compare  = htobe64(compare_add);
	} else {
		aseg->swap_add = htobe64(compare_add);
	}
}