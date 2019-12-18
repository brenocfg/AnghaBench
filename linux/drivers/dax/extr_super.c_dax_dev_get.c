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
struct inode {int i_state; int /*<<< orphan*/  i_data; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_cdev; } ;
struct dax_device {int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  DAXDEV_ALIVE ; 
 scalar_t__ DAXFS_MAGIC ; 
 int /*<<< orphan*/  GFP_USER ; 
 int I_NEW ; 
 int /*<<< orphan*/  S_DAX ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  dax_set ; 
 int /*<<< orphan*/  dax_superblock ; 
 int /*<<< orphan*/  dax_test ; 
 int /*<<< orphan*/  hash_32 (scalar_t__,int) ; 
 struct inode* iget5_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct dax_device* to_dax_dev (struct inode*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static struct dax_device *dax_dev_get(dev_t devt)
{
	struct dax_device *dax_dev;
	struct inode *inode;

	inode = iget5_locked(dax_superblock, hash_32(devt + DAXFS_MAGIC, 31),
			dax_test, dax_set, &devt);

	if (!inode)
		return NULL;

	dax_dev = to_dax_dev(inode);
	if (inode->i_state & I_NEW) {
		set_bit(DAXDEV_ALIVE, &dax_dev->flags);
		inode->i_cdev = &dax_dev->cdev;
		inode->i_mode = S_IFCHR;
		inode->i_flags = S_DAX;
		mapping_set_gfp_mask(&inode->i_data, GFP_USER);
		unlock_new_inode(inode);
	}

	return dax_dev;
}