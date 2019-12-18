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
struct cdev {scalar_t__ si_threadcount; int /*<<< orphan*/  si_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  atomic_subtract_rel_long (scalar_t__*,int) ; 
 int /*<<< orphan*/  devmtx ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void	
dev_relthread(struct cdev *dev, int ref)
{

	mtx_assert(&devmtx, MA_NOTOWNED);
	if (!ref)
		return;
	KASSERT(dev->si_threadcount > 0,
	    ("%s threadcount is wrong", dev->si_name));
	atomic_subtract_rel_long(&dev->si_threadcount, 1);
}