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
struct terasic_mtl_softc {int /*<<< orphan*/  mtl_reg_res; } ;
struct cdev {struct terasic_mtl_softc* si_drv1; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static int
terasic_mtl_reg_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct terasic_mtl_softc *sc;
	int error;

	sc = dev->si_drv1;
	error = 0;
	if (trunc_page(offset) == offset &&
	    offset + PAGE_SIZE > offset &&
	    rman_get_size(sc->mtl_reg_res) >= offset + PAGE_SIZE) {
		*paddr = rman_get_start(sc->mtl_reg_res) + offset;
		*memattr = VM_MEMATTR_UNCACHEABLE;
	} else
		error = ENODEV;
	return (error);
}