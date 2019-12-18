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
struct ib_device {int dummy; } ;

/* Variables and functions */
 int _gid_table_setup_one (struct ib_device*) ; 
 int /*<<< orphan*/  gid_table_cleanup_one (struct ib_device*) ; 
 int /*<<< orphan*/  gid_table_release_one (struct ib_device*) ; 
 int roce_rescan_device (struct ib_device*) ; 

__attribute__((used)) static int gid_table_setup_one(struct ib_device *ib_dev)
{
	int err;

	err = _gid_table_setup_one(ib_dev);

	if (err)
		return err;

	err = roce_rescan_device(ib_dev);

	if (err) {
		gid_table_cleanup_one(ib_dev);
		gid_table_release_one(ib_dev);
	}

	return err;
}