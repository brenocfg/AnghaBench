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
typedef  int uint32_t ;
struct mlx4_wqe_ctrl_seg {int fence_size; } ;
struct mlx4_qp {int dummy; } ;

/* Variables and functions */
 int* get_send_wqe (struct mlx4_qp*,int) ; 

__attribute__((used)) static void stamp_send_wqe(struct mlx4_qp *qp, int n)
{
	uint32_t *wqe = get_send_wqe(qp, n);
	int i;
	int ds = (((struct mlx4_wqe_ctrl_seg *)wqe)->fence_size & 0x3f) << 2;

	for (i = 16; i < ds; i += 16)
		wqe[i] = 0xffffffff;
}