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
struct TYPE_2__ {int wqe_shift; } ;
struct mlx5_rwq {void* pbuff; TYPE_1__ rq; } ;

/* Variables and functions */

__attribute__((used)) static void *get_wq_recv_wqe(struct mlx5_rwq *rwq, int n)
{
	return rwq->pbuff  + (n << rwq->rq.wqe_shift);
}