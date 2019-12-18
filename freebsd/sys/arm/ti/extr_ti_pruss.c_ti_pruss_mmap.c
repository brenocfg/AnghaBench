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
struct ti_pruss_softc {int /*<<< orphan*/  sc_mem_res; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 struct ti_pruss_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_pruss_mmap(struct cdev *cdev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	device_t dev = cdev->si_drv1;
	struct ti_pruss_softc *sc = device_get_softc(dev);

	if (offset >= rman_get_size(sc->sc_mem_res))
		return (ENOSPC);
	*paddr = rman_get_start(sc->sc_mem_res) + offset;
	*memattr = VM_MEMATTR_UNCACHEABLE;

	return (0);
}