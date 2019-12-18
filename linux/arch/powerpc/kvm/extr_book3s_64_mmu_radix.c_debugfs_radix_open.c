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
struct kvm {int dummy; } ;
struct inode {struct kvm* i_private; } ;
struct file {struct debugfs_radix_state* private_data; } ;
struct debugfs_radix_state {int /*<<< orphan*/  mutex; struct kvm* kvm; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kvm_get_kvm (struct kvm*) ; 
 struct debugfs_radix_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nonseekable_open (struct inode*,struct file*) ; 

__attribute__((used)) static int debugfs_radix_open(struct inode *inode, struct file *file)
{
	struct kvm *kvm = inode->i_private;
	struct debugfs_radix_state *p;

	p = kzalloc(sizeof(*p), GFP_KERNEL);
	if (!p)
		return -ENOMEM;

	kvm_get_kvm(kvm);
	p->kvm = kvm;
	mutex_init(&p->mutex);
	file->private_data = p;

	return nonseekable_open(inode, file);
}