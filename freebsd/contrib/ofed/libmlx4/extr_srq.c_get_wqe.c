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
struct TYPE_2__ {void* buf; } ;
struct mlx4_srq {int wqe_shift; TYPE_1__ buf; } ;

/* Variables and functions */

__attribute__((used)) static void *get_wqe(struct mlx4_srq *srq, int n)
{
	return srq->buf.buf + (n << srq->wqe_shift);
}