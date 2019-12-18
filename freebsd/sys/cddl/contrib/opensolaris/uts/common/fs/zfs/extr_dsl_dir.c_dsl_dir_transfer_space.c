#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/  dd_dbuf; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  size_t dd_used_t ;
struct TYPE_6__ {int dd_flags; scalar_t__ dd_used_bytes; int /*<<< orphan*/ * dd_used_breakdown; } ;

/* Variables and functions */
 scalar_t__ ABS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT (int) ; 
 int DD_FLAG_USED_BREAKDOWN ; 
 size_t DD_USED_NUM ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_tx_is_syncing (int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_dir_transfer_space(dsl_dir_t *dd, int64_t delta,
    dd_used_t oldtype, dd_used_t newtype, dmu_tx_t *tx)
{
	ASSERT(tx == NULL || dmu_tx_is_syncing(tx));
	ASSERT(oldtype < DD_USED_NUM);
	ASSERT(newtype < DD_USED_NUM);

	if (delta == 0 ||
	    !(dsl_dir_phys(dd)->dd_flags & DD_FLAG_USED_BREAKDOWN))
		return;

	if (tx != NULL)
		dmu_buf_will_dirty(dd->dd_dbuf, tx);
	mutex_enter(&dd->dd_lock);
	ASSERT(delta > 0 ?
	    dsl_dir_phys(dd)->dd_used_breakdown[oldtype] >= delta :
	    dsl_dir_phys(dd)->dd_used_breakdown[newtype] >= -delta);
	ASSERT(dsl_dir_phys(dd)->dd_used_bytes >= ABS(delta));
	dsl_dir_phys(dd)->dd_used_breakdown[oldtype] -= delta;
	dsl_dir_phys(dd)->dd_used_breakdown[newtype] += delta;
	mutex_exit(&dd->dd_lock);
}