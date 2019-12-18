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
 int drbd_single_open (struct file*,int /*<<< orphan*/ ,struct drbd_resource*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_flight_summary_show ; 

__attribute__((used)) static int in_flight_summary_open(struct inode *inode, struct file *file)
{
	struct drbd_resource *resource = inode->i_private;
	return drbd_single_open(file, in_flight_summary_show, resource,
				&resource->kref, drbd_destroy_resource);
}