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
struct bhnd_softc {int dummy; } ;
struct bcma_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_free_dinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bcma_devinfo*) ; 
 int /*<<< orphan*/  bhnd_generic_child_deleted (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bcma_devinfo* device_get_ivars (int /*<<< orphan*/ ) ; 
 struct bhnd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bcma_child_deleted(device_t dev, device_t child)
{
	struct bhnd_softc	*sc;
	struct bcma_devinfo	*dinfo;

	sc = device_get_softc(dev);

	/* Call required bhnd(4) implementation */
	bhnd_generic_child_deleted(dev, child);

	/* Free bcma device info */
	if ((dinfo = device_get_ivars(child)) != NULL)
		bcma_free_dinfo(dev, child, dinfo);

	device_set_ivars(child, NULL);
}