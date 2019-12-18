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
typedef  int u32 ;
struct ib_wq {int /*<<< orphan*/  usecnt; } ;
struct ib_rwq_ind_table {int log_ind_tbl_size; TYPE_1__* device; int /*<<< orphan*/  usecnt; struct ib_wq** ind_tbl; } ;
struct TYPE_2__ {int (* destroy_rwq_ind_table ) (struct ib_rwq_ind_table*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct ib_rwq_ind_table*) ; 

int ib_destroy_rwq_ind_table(struct ib_rwq_ind_table *rwq_ind_table)
{
	int err, i;
	u32 table_size = (1 << rwq_ind_table->log_ind_tbl_size);
	struct ib_wq **ind_tbl = rwq_ind_table->ind_tbl;

	if (atomic_read(&rwq_ind_table->usecnt))
		return -EBUSY;

	err = rwq_ind_table->device->destroy_rwq_ind_table(rwq_ind_table);
	if (!err) {
		for (i = 0; i < table_size; i++)
			atomic_dec(&ind_tbl[i]->usecnt);
	}

	return err;
}