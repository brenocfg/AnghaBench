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
struct seq_file {int dummy; } ;
struct hypfs_sb_info {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct dentry {TYPE_1__* d_sb; } ;
struct TYPE_2__ {struct hypfs_sb_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  from_kgid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  from_kuid_munged (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hypfs_show_options(struct seq_file *s, struct dentry *root)
{
	struct hypfs_sb_info *hypfs_info = root->d_sb->s_fs_info;

	seq_printf(s, ",uid=%u", from_kuid_munged(&init_user_ns, hypfs_info->uid));
	seq_printf(s, ",gid=%u", from_kgid_munged(&init_user_ns, hypfs_info->gid));
	return 0;
}