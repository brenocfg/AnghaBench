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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/ * dd_parent; int /*<<< orphan*/  dd_dbuf; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_6__ {int /*<<< orphan*/  dd_reserved; int /*<<< orphan*/  dd_used_bytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DD_USED_CHILD_RSRV ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dir_phys (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_dir_set_reservation_sync_impl(dsl_dir_t *dd, uint64_t value, dmu_tx_t *tx)
{
	uint64_t used;
	int64_t delta;

	dmu_buf_will_dirty(dd->dd_dbuf, tx);

	mutex_enter(&dd->dd_lock);
	used = dsl_dir_phys(dd)->dd_used_bytes;
	delta = MAX(used, value) - MAX(used, dsl_dir_phys(dd)->dd_reserved);
	dsl_dir_phys(dd)->dd_reserved = value;

	if (dd->dd_parent != NULL) {
		/* Roll up this additional usage into our ancestors */
		dsl_dir_diduse_space(dd->dd_parent, DD_USED_CHILD_RSRV,
		    delta, 0, 0, tx);
	}
	mutex_exit(&dd->dd_lock);
}