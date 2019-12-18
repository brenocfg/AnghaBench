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
struct vmmdev_softc {int dummy; } ;
struct cdev {struct vmmdev_softc* si_drv1; } ;

/* Variables and functions */

__attribute__((used)) static struct vmmdev_softc *
vmmdev_lookup2(struct cdev *cdev)
{

	return (cdev->si_drv1);
}