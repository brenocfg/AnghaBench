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
struct TYPE_4__ {int /*<<< orphan*/  alloc; } ;
struct TYPE_3__ {scalar_t__ reserved_uars; scalar_t__ num_uars; } ;
struct mthca_dev {TYPE_2__ uar_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int /*<<< orphan*/  mthca_alloc_cleanup (int /*<<< orphan*/ *) ; 
 int mthca_alloc_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__) ; 
 int mthca_init_db_tab (struct mthca_dev*) ; 

int mthca_init_uar_table(struct mthca_dev *dev)
{
	int ret;

	ret = mthca_alloc_init(&dev->uar_table.alloc,
			       dev->limits.num_uars,
			       dev->limits.num_uars - 1,
			       dev->limits.reserved_uars + 1);
	if (ret)
		return ret;

	ret = mthca_init_db_tab(dev);
	if (ret)
		mthca_alloc_cleanup(&dev->uar_table.alloc);

	return ret;
}