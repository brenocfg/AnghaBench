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
struct super_block {struct binderfs_info* s_fs_info; } ;
struct binderfs_info {scalar_t__ ipc_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct binderfs_info*) ; 
 int /*<<< orphan*/  kill_litter_super (struct super_block*) ; 
 int /*<<< orphan*/  put_ipc_ns (scalar_t__) ; 

__attribute__((used)) static void binderfs_kill_super(struct super_block *sb)
{
	struct binderfs_info *info = sb->s_fs_info;

	kill_litter_super(sb);

	if (info && info->ipc_ns)
		put_ipc_ns(info->ipc_ns);

	kfree(info);
}