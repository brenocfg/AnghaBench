#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_flags; TYPE_1__* i_mapping; } ;
struct file {struct dev_dax* private_data; TYPE_1__* f_mapping; int /*<<< orphan*/  f_wb_err; } ;
struct dev_dax {int /*<<< orphan*/  dev; } ;
struct dax_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_DAX ; 
 struct dev_dax* dax_get_private (struct dax_device*) ; 
 struct inode* dax_inode (struct dax_device*) ; 
 int /*<<< orphan*/  dev_dax_aops ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  filemap_sample_wb_err (TYPE_1__*) ; 
 struct dax_device* inode_dax (struct inode*) ; 

__attribute__((used)) static int dax_open(struct inode *inode, struct file *filp)
{
	struct dax_device *dax_dev = inode_dax(inode);
	struct inode *__dax_inode = dax_inode(dax_dev);
	struct dev_dax *dev_dax = dax_get_private(dax_dev);

	dev_dbg(&dev_dax->dev, "trace\n");
	inode->i_mapping = __dax_inode->i_mapping;
	inode->i_mapping->host = __dax_inode;
	inode->i_mapping->a_ops = &dev_dax_aops;
	filp->f_mapping = inode->i_mapping;
	filp->f_wb_err = filemap_sample_wb_err(filp->f_mapping);
	filp->private_data = dev_dax;
	inode->i_flags = S_DAX;

	return 0;
}