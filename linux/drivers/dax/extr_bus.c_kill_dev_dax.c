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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct dev_dax {struct dax_device* dax_dev; } ;
struct dax_device {int dummy; } ;

/* Variables and functions */
 struct inode* dax_inode (struct dax_device*) ; 
 int /*<<< orphan*/  kill_dax (struct dax_device*) ; 
 int /*<<< orphan*/  unmap_mapping_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void kill_dev_dax(struct dev_dax *dev_dax)
{
	struct dax_device *dax_dev = dev_dax->dax_dev;
	struct inode *inode = dax_inode(dax_dev);

	kill_dax(dax_dev);
	unmap_mapping_range(inode->i_mapping, 0, 0, 1);
}