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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
struct agp_softc {int /*<<< orphan*/ * as_aperture; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ AGP_GET_APERTURE (int /*<<< orphan*/ ) ; 
 struct agp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
agp_mmap(struct cdev *kdev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	device_t dev = kdev->si_drv1;
	struct agp_softc *sc = device_get_softc(dev);

	if (offset > AGP_GET_APERTURE(dev))
		return -1;
	if (sc->as_aperture == NULL)
		return -1;
	*paddr = rman_get_start(sc->as_aperture) + offset;
	return 0;
}