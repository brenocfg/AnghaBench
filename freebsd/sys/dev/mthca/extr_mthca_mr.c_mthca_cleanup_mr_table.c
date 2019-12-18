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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mpt_base; scalar_t__ mtt_base; int /*<<< orphan*/  mtt_buddy; } ;
struct TYPE_6__ {int /*<<< orphan*/  mpt_alloc; TYPE_2__ tavor_fmr; int /*<<< orphan*/  mtt_buddy; } ;
struct TYPE_4__ {scalar_t__ fmr_reserved_mtts; } ;
struct mthca_dev {TYPE_3__ mr_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mthca_buddy_cleanup (int /*<<< orphan*/ *) ; 

void mthca_cleanup_mr_table(struct mthca_dev *dev)
{
	/* XXX check if any MRs are still allocated? */
	if (dev->limits.fmr_reserved_mtts)
		mthca_buddy_cleanup(&dev->mr_table.tavor_fmr.mtt_buddy);

	mthca_buddy_cleanup(&dev->mr_table.mtt_buddy);

	if (dev->mr_table.tavor_fmr.mtt_base)
		iounmap(dev->mr_table.tavor_fmr.mtt_base);
	if (dev->mr_table.tavor_fmr.mpt_base)
		iounmap(dev->mr_table.tavor_fmr.mpt_base);

	mthca_alloc_cleanup(&dev->mr_table.mpt_alloc);
}