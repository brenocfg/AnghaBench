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
struct gdt_softc {int dummy; } ;
struct cdev {struct gdt_softc* si_drv1; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/ * devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/ * devclass_find (char*) ; 
 int /*<<< orphan*/ * devclass_get_device (int /*<<< orphan*/ *,int) ; 
 struct gdt_softc* device_get_softc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct gdt_softc *
gdt_minor2softc(struct cdev *dev, int minor_no)
{
#ifdef SDEV_PER_HBA

    return (dev->si_drv1);
#else
    devclass_t dc;
    device_t child;

    dc = devclass_find("iir");
    if (dc == NULL)
	return (NULL);
    child = devclass_get_device(dc, minor_no);
    if (child == NULL)
	return (NULL);
    return (device_get_softc(child));
#endif
}