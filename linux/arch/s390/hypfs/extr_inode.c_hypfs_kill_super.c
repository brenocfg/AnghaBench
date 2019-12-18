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
struct super_block {struct hypfs_sb_info* s_fs_info; scalar_t__ s_root; } ;
struct hypfs_sb_info {scalar_t__ update_file; } ;

/* Variables and functions */
 int /*<<< orphan*/  hypfs_delete_tree (scalar_t__) ; 
 int /*<<< orphan*/  hypfs_remove (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct hypfs_sb_info*) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 

__attribute__((used)) static void hypfs_kill_super(struct super_block *sb)
{
	struct hypfs_sb_info *sb_info = sb->s_fs_info;

	if (sb->s_root)
		hypfs_delete_tree(sb->s_root);
	if (sb_info && sb_info->update_file)
		hypfs_remove(sb_info->update_file);
	kfree(sb->s_fs_info);
	sb->s_fs_info = NULL;
	kill_litter_super(sb);
}