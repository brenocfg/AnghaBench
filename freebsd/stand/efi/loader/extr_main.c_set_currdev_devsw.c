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
struct devsw {int dummy; } ;
struct devdesc {int d_unit; struct devsw* d_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_currdev_devdesc (struct devdesc*) ; 

__attribute__((used)) static void
set_currdev_devsw(struct devsw *dev, int unit)
{
	struct devdesc currdev;

	currdev.d_dev = dev;
	currdev.d_unit = unit;

	set_currdev_devdesc(&currdev);
}