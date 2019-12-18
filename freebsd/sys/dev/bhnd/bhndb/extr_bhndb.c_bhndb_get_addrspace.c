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
struct bhndb_softc {int /*<<< orphan*/ * dev; } ;
struct bhndb_devinfo {int /*<<< orphan*/  addrspace; } ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  bhndb_addrspace ;

/* Variables and functions */
 struct bhndb_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

bhndb_addrspace
bhndb_get_addrspace(struct bhndb_softc *sc, device_t child)
{
	struct bhndb_devinfo	*dinfo;
	device_t		 imd_dev;

	/* Find the directly attached parent of the requesting device */
	imd_dev = child;
	while (imd_dev != NULL && device_get_parent(imd_dev) != sc->dev)
		imd_dev = device_get_parent(imd_dev);

	if (imd_dev == NULL)
		panic("bhndb address space request for non-child device %s\n",
		     device_get_nameunit(child));

	dinfo = device_get_ivars(imd_dev);
	return (dinfo->addrspace);
}