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
struct TYPE_4__ {int /*<<< orphan*/  alloc; int /*<<< orphan*/  srq; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_srqs; } ;
struct mthca_dev {int mthca_flags; TYPE_2__ srq_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int MTHCA_FLAG_SRQ ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_array_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mthca_cleanup_srq_table(struct mthca_dev *dev)
{
	if (!(dev->mthca_flags & MTHCA_FLAG_SRQ))
		return;

	mthca_array_cleanup(&dev->srq_table.srq, dev->limits.num_srqs);
	mthca_alloc_cleanup(&dev->srq_table.alloc);
}