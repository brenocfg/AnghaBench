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
struct inode {struct drbd_resource* i_private; } ;
struct file {int dummy; } ;
struct drbd_resource {int /*<<< orphan*/  kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_destroy_resource ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int single_release (struct inode*,struct file*) ; 

__attribute__((used)) static int in_flight_summary_release(struct inode *inode, struct file *file)
{
	struct drbd_resource *resource = inode->i_private;
	kref_put(&resource->kref, drbd_destroy_resource);
	return single_release(inode, file);
}