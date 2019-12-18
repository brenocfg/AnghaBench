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
typedef  int u32 ;
struct mlx5_cqwq {int log_stride; } ;

/* Variables and functions */
 int mlx5_cqwq_get_size (struct mlx5_cqwq*) ; 

__attribute__((used)) static u32 mlx5_cqwq_get_byte_size(struct mlx5_cqwq *wq)
{
	return mlx5_cqwq_get_size(wq) << wq->log_stride;
}