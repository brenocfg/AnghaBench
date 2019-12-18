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
struct dax_device {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAXDEV_ALIVE ; 
 int /*<<< orphan*/  WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dax_device* to_dax_dev (struct inode*) ; 

__attribute__((used)) static void dax_destroy_inode(struct inode *inode)
{
	struct dax_device *dax_dev = to_dax_dev(inode);
	WARN_ONCE(test_bit(DAXDEV_ALIVE, &dax_dev->flags),
			"kill_dax() must be called before final iput()\n");
}