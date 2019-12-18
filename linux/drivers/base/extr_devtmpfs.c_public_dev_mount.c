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
struct super_block {int /*<<< orphan*/  s_root; int /*<<< orphan*/  s_umount; int /*<<< orphan*/  s_active; } ;
struct file_system_type {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct super_block* mnt_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct dentry* dget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 TYPE_1__* mnt ; 

__attribute__((used)) static struct dentry *public_dev_mount(struct file_system_type *fs_type, int flags,
		      const char *dev_name, void *data)
{
	struct super_block *s = mnt->mnt_sb;
	atomic_inc(&s->s_active);
	down_write(&s->s_umount);
	return dget(s->s_root);
}