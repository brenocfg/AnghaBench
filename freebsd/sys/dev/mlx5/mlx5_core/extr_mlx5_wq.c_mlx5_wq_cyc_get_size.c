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
struct mlx5_wq_cyc {scalar_t__ sz_m1; } ;

/* Variables and functions */

u32 mlx5_wq_cyc_get_size(struct mlx5_wq_cyc *wq)
{
	return (u32)wq->sz_m1 + 1;
}