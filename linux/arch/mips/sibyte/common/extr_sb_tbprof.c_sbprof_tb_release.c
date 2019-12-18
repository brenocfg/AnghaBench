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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {scalar_t__ open; int /*<<< orphan*/  lock; int /*<<< orphan*/  sbprof_tbbuf; scalar_t__ tb_enable; scalar_t__ tb_armed; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ SB_CLOSED ; 
 int iminor (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ sbp ; 
 int /*<<< orphan*/  sbprof_zbprof_stop () ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int sbprof_tb_release(struct inode *inode, struct file *filp)
{
	int minor;

	minor = iminor(inode);
	if (minor != 0 || sbp.open != SB_CLOSED)
		return -ENODEV;

	mutex_lock(&sbp.lock);

	if (sbp.tb_armed || sbp.tb_enable)
		sbprof_zbprof_stop();

	vfree(sbp.sbprof_tbbuf);
	sbp.open = SB_CLOSED;
	wmb();

	mutex_unlock(&sbp.lock);

	return 0;
}