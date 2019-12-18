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
struct mlx5_fpga_device {TYPE_1__* trans; } ;
struct TYPE_4__ {int tid; int /*<<< orphan*/  list_item; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_queue; TYPE_2__* transactions; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int mlx5_fpga_trans_device_init(struct mlx5_fpga_device *fdev)
{
	int ret = 0;
	int tid;

	fdev->trans = kzalloc(sizeof(*fdev->trans), GFP_KERNEL);
	if (!fdev->trans) {
		ret = -ENOMEM;
		goto out;
	}

	INIT_LIST_HEAD(&fdev->trans->free_queue);
	for (tid = 0; tid < ARRAY_SIZE(fdev->trans->transactions); tid++) {
		fdev->trans->transactions[tid].tid = tid;
		list_add_tail(&fdev->trans->transactions[tid].list_item,
			      &fdev->trans->free_queue);
	}

	spin_lock_init(&fdev->trans->lock);

out:
	return ret;
}