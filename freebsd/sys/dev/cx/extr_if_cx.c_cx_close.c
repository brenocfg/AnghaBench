#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int dummy; } ;
struct cdev {TYPE_1__* si_drv1; } ;
struct TYPE_3__ {int open_dev; } ;
typedef  TYPE_1__ drv_t ;

/* Variables and functions */
 int /*<<< orphan*/  CX_DEBUG2 (TYPE_1__*,char*) ; 

__attribute__((used)) static int cx_close (struct cdev *dev, int flag, int mode, struct thread *td)
{
	drv_t *d;

	d = dev->si_drv1;
	CX_DEBUG2 (d, ("cx_close\n"));
	d->open_dev &= ~0x1;
	return 0;
}