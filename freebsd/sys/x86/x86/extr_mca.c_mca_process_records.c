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
struct mca_internal {int /*<<< orphan*/  rec; } ;
typedef  enum scan_mode { ____Placeholder_scan_mode } scan_mode ;

/* Variables and functions */
 int POLLED ; 
 struct mca_internal* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cold ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mca_lock ; 
 int /*<<< orphan*/  mca_log (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mca_pending ; 
 int /*<<< orphan*/  mca_resize_freelist () ; 
 int /*<<< orphan*/  mca_resize_task ; 
 int /*<<< orphan*/  mca_store_record (struct mca_internal*) ; 
 int /*<<< orphan*/  mca_tq ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mca_process_records(enum scan_mode mode)
{
	struct mca_internal *mca;

	mtx_lock_spin(&mca_lock);
	while ((mca = STAILQ_FIRST(&mca_pending)) != NULL) {
		STAILQ_REMOVE_HEAD(&mca_pending, link);
		mca_log(&mca->rec);
		mca_store_record(mca);
	}
	mtx_unlock_spin(&mca_lock);
	if (mode == POLLED)
		mca_resize_freelist();
	else if (!cold)
		taskqueue_enqueue(mca_tq, &mca_resize_task);
}