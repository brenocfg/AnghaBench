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
struct thread {int dummy; } ;
struct mqfs_node {int dummy; } ;
struct file {struct mqfs_node* f_data; int /*<<< orphan*/ * f_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  badfileops ; 
 TYPE_1__ mqfs_data ; 
 int /*<<< orphan*/  mqnode_release (struct mqfs_node*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqf_close(struct file *fp, struct thread *td)
{
	struct mqfs_node *pn;

	fp->f_ops = &badfileops;
	pn = fp->f_data;
	fp->f_data = NULL;
	sx_xlock(&mqfs_data.mi_lock);
	mqnode_release(pn);
	sx_xunlock(&mqfs_data.mi_lock);
	return (0);
}