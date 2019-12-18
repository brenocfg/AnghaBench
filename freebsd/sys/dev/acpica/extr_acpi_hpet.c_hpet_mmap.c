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
struct hpet_softc {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  mmap_allow_write; } ;
struct cdev {struct hpet_softc* si_drv1; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
hpet_mmap(struct cdev *cdev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct hpet_softc *sc;

	sc = cdev->si_drv1;
	if (offset >= rman_get_size(sc->mem_res))
		return (EINVAL);
	if (!sc->mmap_allow_write && (nprot & PROT_WRITE))
		return (EPERM);
	*paddr = rman_get_start(sc->mem_res) + offset;
	*memattr = VM_MEMATTR_UNCACHEABLE;

	return (0);
}