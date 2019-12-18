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
struct drbd_resource {char* name; struct dentry* debugfs_res_in_flight_summary; struct dentry* debugfs_res; struct dentry* debugfs_res_connections; struct dentry* debugfs_res_volumes; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 struct dentry* debugfs_create_file (char*,int,struct dentry*,struct drbd_resource*,int /*<<< orphan*/ *) ; 
 struct dentry* drbd_debugfs_resources ; 
 int /*<<< orphan*/  in_flight_summary_fops ; 

void drbd_debugfs_resource_add(struct drbd_resource *resource)
{
	struct dentry *dentry;

	dentry = debugfs_create_dir(resource->name, drbd_debugfs_resources);
	resource->debugfs_res = dentry;

	dentry = debugfs_create_dir("volumes", resource->debugfs_res);
	resource->debugfs_res_volumes = dentry;

	dentry = debugfs_create_dir("connections", resource->debugfs_res);
	resource->debugfs_res_connections = dentry;

	dentry = debugfs_create_file("in_flight_summary", 0440,
				     resource->debugfs_res, resource,
				     &in_flight_summary_fops);
	resource->debugfs_res_in_flight_summary = dentry;
}