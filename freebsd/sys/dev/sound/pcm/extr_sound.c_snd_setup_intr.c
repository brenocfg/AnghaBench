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
struct snddev_info {int /*<<< orphan*/  flags; } ;
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_AV ; 
 int /*<<< orphan*/  SD_F_MPSAFE ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,void**) ; 
 struct snddev_info* device_get_softc (int /*<<< orphan*/ ) ; 

int
snd_setup_intr(device_t dev, struct resource *res, int flags, driver_intr_t hand, void *param, void **cookiep)
{
	struct snddev_info *d;

	flags &= INTR_MPSAFE;
	flags |= INTR_TYPE_AV;
	d = device_get_softc(dev);
	if (d != NULL && (flags & INTR_MPSAFE))
		d->flags |= SD_F_MPSAFE;

	return bus_setup_intr(dev, res, flags, NULL, hand, param, cookiep);
}