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
struct cdev {struct beri_mem_softc* si_drv1; } ;
struct beri_mem_softc {scalar_t__ mem_size; scalar_t__ mem_start; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
mem_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr, int nprot,
    vm_memattr_t *memattr)
{
	struct beri_mem_softc *sc;

	sc = dev->si_drv1;

	if (offset < sc->mem_size) {
		*paddr = sc->mem_start + offset;
		return (0);
        }

	return (EINVAL);
}