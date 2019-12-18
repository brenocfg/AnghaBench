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
struct inode {int dummy; } ;
struct file {struct debugfs_radix_state* private_data; } ;
struct debugfs_radix_state {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct debugfs_radix_state*) ; 
 int /*<<< orphan*/  kvm_put_kvm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int debugfs_radix_release(struct inode *inode, struct file *file)
{
	struct debugfs_radix_state *p = file->private_data;

	kvm_put_kvm(p->kvm);
	kfree(p);
	return 0;
}