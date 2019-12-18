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
struct inode {scalar_t__ i_rdev; } ;
struct dax_device {int /*<<< orphan*/ * host; } ;

/* Variables and functions */
 int /*<<< orphan*/  MINOR (scalar_t__) ; 
 int /*<<< orphan*/  dax_cache ; 
 int /*<<< orphan*/  dax_minor_ida ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dax_device*) ; 
 struct dax_device* to_dax_dev (struct inode*) ; 

__attribute__((used)) static void dax_free_inode(struct inode *inode)
{
	struct dax_device *dax_dev = to_dax_dev(inode);
	kfree(dax_dev->host);
	dax_dev->host = NULL;
	if (inode->i_rdev)
		ida_simple_remove(&dax_minor_ida, MINOR(inode->i_rdev));
	kmem_cache_free(dax_cache, dax_dev);
}