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
struct mlx4_xsrq_table {int num_xsrq; int shift; int mask; int /*<<< orphan*/  mutex; TYPE_1__* xsrq_table; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** table; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void mlx4_clear_xsrq(struct mlx4_xsrq_table *xsrq_table, uint32_t srqn)
{
	int index;

	index = (srqn & (xsrq_table->num_xsrq - 1)) >> xsrq_table->shift;
	pthread_mutex_lock(&xsrq_table->mutex);

	if (--xsrq_table->xsrq_table[index].refcnt)
		xsrq_table->xsrq_table[index].table[srqn & xsrq_table->mask] = NULL;
	else
		free(xsrq_table->xsrq_table[index].table);

	pthread_mutex_unlock(&xsrq_table->mutex);
}