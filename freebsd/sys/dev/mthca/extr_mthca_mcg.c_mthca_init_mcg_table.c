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
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  alloc; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_mgms; int /*<<< orphan*/  num_amgms; } ;
struct mthca_dev {TYPE_2__ mcg_table; TYPE_1__ limits; } ;

/* Variables and functions */
 int mthca_alloc_init (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mthca_init_mcg_table(struct mthca_dev *dev)
{
	int err;
	int table_size = dev->limits.num_mgms + dev->limits.num_amgms;

	err = mthca_alloc_init(&dev->mcg_table.alloc,
			       table_size,
			       table_size - 1,
			       dev->limits.num_mgms);
	if (err)
		return err;

	mutex_init(&dev->mcg_table.mutex);

	return 0;
}