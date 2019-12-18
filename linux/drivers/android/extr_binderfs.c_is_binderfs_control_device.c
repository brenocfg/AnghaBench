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
struct dentry {TYPE_1__* d_sb; } ;
struct binderfs_info {struct dentry const* control_dentry; } ;
struct TYPE_2__ {struct binderfs_info* s_fs_info; } ;

/* Variables and functions */

__attribute__((used)) static inline bool is_binderfs_control_device(const struct dentry *dentry)
{
	struct binderfs_info *info = dentry->d_sb->s_fs_info;
	return info->control_dentry == dentry;
}