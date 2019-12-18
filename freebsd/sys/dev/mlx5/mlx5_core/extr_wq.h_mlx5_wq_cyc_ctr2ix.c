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
typedef  int u16 ;
struct mlx5_wq_cyc {int sz_m1; } ;

/* Variables and functions */

__attribute__((used)) static inline u16 mlx5_wq_cyc_ctr2ix(struct mlx5_wq_cyc *wq, u16 ctr)
{
	return ctr & wq->sz_m1;
}