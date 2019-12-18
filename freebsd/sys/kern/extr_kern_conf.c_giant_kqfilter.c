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
struct knote {int dummy; } ;
struct cdevsw {TYPE_1__* d_gianttrick; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int (* d_kqfilter ) (struct cdev*,struct knote*) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 struct cdevsw* dev_refthread (struct cdev*,int*) ; 
 int /*<<< orphan*/  dev_relthread (struct cdev*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct cdev*,struct knote*) ; 

__attribute__((used)) static int
giant_kqfilter(struct cdev *dev, struct knote *kn)
{
	struct cdevsw *dsw;
	int ref, retval;

	dsw = dev_refthread(dev, &ref);
	if (dsw == NULL)
		return (ENXIO);
	mtx_lock(&Giant);
	retval = dsw->d_gianttrick->d_kqfilter(dev, kn);
	mtx_unlock(&Giant);
	dev_relthread(dev, ref);
	return (retval);
}