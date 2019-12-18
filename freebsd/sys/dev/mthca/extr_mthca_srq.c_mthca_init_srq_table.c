#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  srq; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {scalar_t__ num_srqs; int /*<<< orphan*/  reserved_srqs; } ;
struct mthca_dev {int mthca_flags; TYPE_2__ srq_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int MTHCA_FLAG_SRQ ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int mthca_alloc_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int mthca_array_init (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mthca_init_srq_table(struct mthca_dev *dev)
{
	int err;

	if (!(dev->mthca_flags & MTHCA_FLAG_SRQ))
		return 0;

	spin_lock_init(&dev->srq_table.lock);

	err = mthca_alloc_init(&dev->srq_table.alloc,
			       dev->limits.num_srqs,
			       dev->limits.num_srqs - 1,
			       dev->limits.reserved_srqs);
	if (err)
		return err;

	err = mthca_array_init(&dev->srq_table.srq,
			       dev->limits.num_srqs);
	if (err)
		mthca_alloc_cleanup(&dev->srq_table.alloc);

	return err;
}