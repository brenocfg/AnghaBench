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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct bt_bmc {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clr_b_busy (struct bt_bmc*) ; 
 struct bt_bmc* file_bt_bmc (struct file*) ; 
 int /*<<< orphan*/  open_count ; 

__attribute__((used)) static int bt_bmc_open(struct inode *inode, struct file *file)
{
	struct bt_bmc *bt_bmc = file_bt_bmc(file);

	if (atomic_inc_return(&open_count) == 1) {
		clr_b_busy(bt_bmc);
		return 0;
	}

	atomic_dec(&open_count);
	return -EBUSY;
}