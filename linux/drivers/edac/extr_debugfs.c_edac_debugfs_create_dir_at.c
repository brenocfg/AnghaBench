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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char const*,struct dentry*) ; 

struct dentry *
edac_debugfs_create_dir_at(const char *dirname, struct dentry *parent)
{
	return debugfs_create_dir(dirname, parent);
}