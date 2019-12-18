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
typedef  scalar_t__ u32 ;
struct mlx5_cqwq {scalar_t__ sz_m1; } ;

/* Variables and functions */

u32 mlx5_cqwq_get_size(struct mlx5_cqwq *wq)
{
	return wq->sz_m1 + 1;
}