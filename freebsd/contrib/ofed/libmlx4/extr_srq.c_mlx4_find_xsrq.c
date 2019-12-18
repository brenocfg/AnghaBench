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
typedef  int uint32_t ;
struct mlx4_xsrq_table {int num_xsrq; int shift; int mask; TYPE_1__* xsrq_table; } ;
struct mlx4_srq {int dummy; } ;
struct TYPE_2__ {struct mlx4_srq** table; scalar_t__ refcnt; } ;

/* Variables and functions */

struct mlx4_srq *mlx4_find_xsrq(struct mlx4_xsrq_table *xsrq_table, uint32_t srqn)
{
	int index;

	index = (srqn & (xsrq_table->num_xsrq - 1)) >> xsrq_table->shift;
	if (xsrq_table->xsrq_table[index].refcnt)
		return xsrq_table->xsrq_table[index].table[srqn & xsrq_table->mask];

	return NULL;
}