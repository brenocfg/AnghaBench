#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct cdev {TYPE_2__* si_drv1; } ;
struct TYPE_5__ {int open_dev; TYPE_1__* chan; } ;
typedef  TYPE_2__ drv_t ;
struct TYPE_4__ {int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_2__*,char*) ; 

__attribute__((used)) static int cx_open (struct cdev *dev, int flag, int mode, struct thread *td)
{
	int unit;
	drv_t *d;

	d = dev->si_drv1;
	unit = d->chan->num;

	CX_DEBUG2 (d, ("cx_open unit=%d, flag=0x%x, mode=0x%x\n",
		    unit, flag, mode));

	d->open_dev |= 0x1;

	CX_DEBUG2 (d, ("cx_open done\n"));

	return 0;
}