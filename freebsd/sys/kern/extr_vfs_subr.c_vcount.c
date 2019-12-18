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
struct vnode {TYPE_1__* v_rdev; } ;
struct TYPE_2__ {int si_usecount; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 

int
vcount(struct vnode *vp)
{
	int count;

	dev_lock();
	count = vp->v_rdev->si_usecount;
	dev_unlock();
	return (count);
}