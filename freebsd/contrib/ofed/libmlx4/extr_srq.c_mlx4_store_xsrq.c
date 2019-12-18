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
struct mlx4_srq {int dummy; } ;
struct TYPE_2__ {struct mlx4_srq** table; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 struct mlx4_srq** calloc (int,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

int mlx4_store_xsrq(struct mlx4_xsrq_table *xsrq_table, uint32_t srqn,
		    struct mlx4_srq *srq)
{
	int index, ret = 0;

	index = (srqn & (xsrq_table->num_xsrq - 1)) >> xsrq_table->shift;
	pthread_mutex_lock(&xsrq_table->mutex);
	if (!xsrq_table->xsrq_table[index].refcnt) {
		xsrq_table->xsrq_table[index].table = calloc(xsrq_table->mask + 1,
							     sizeof(struct mlx4_srq *));
		if (!xsrq_table->xsrq_table[index].table) {
			ret = -1;
			goto out;
		}
	}

	xsrq_table->xsrq_table[index].refcnt++;
	xsrq_table->xsrq_table[index].table[srqn & xsrq_table->mask] = srq;

out:
	pthread_mutex_unlock(&xsrq_table->mutex);
	return ret;
}