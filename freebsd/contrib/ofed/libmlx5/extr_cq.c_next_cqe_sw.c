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
struct mlx5_cq {int /*<<< orphan*/  cons_index; } ;

/* Variables and functions */
 void* get_sw_cqe (struct mlx5_cq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *next_cqe_sw(struct mlx5_cq *cq)
{
	return get_sw_cqe(cq, cq->cons_index);
}