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
struct mlx4_wqe_atomic_seg {void* compare; void* swap_add; } ;
struct TYPE_3__ {int /*<<< orphan*/  compare_add; int /*<<< orphan*/  swap; } ;
struct TYPE_4__ {TYPE_1__ atomic; } ;
struct ibv_send_wr {scalar_t__ opcode; TYPE_2__ wr; } ;

/* Variables and functions */
 scalar_t__ IBV_WR_ATOMIC_CMP_AND_SWP ; 
 void* htobe64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_atomic_seg(struct mlx4_wqe_atomic_seg *aseg, struct ibv_send_wr *wr)
{
	if (wr->opcode == IBV_WR_ATOMIC_CMP_AND_SWP) {
		aseg->swap_add = htobe64(wr->wr.atomic.swap);
		aseg->compare  = htobe64(wr->wr.atomic.compare_add);
	} else {
		aseg->swap_add = htobe64(wr->wr.atomic.compare_add);
		aseg->compare  = 0;
	}

}