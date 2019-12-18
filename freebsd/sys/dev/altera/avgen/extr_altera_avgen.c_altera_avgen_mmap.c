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
struct cdev {struct altera_avgen_softc* si_drv1; } ;
struct altera_avgen_softc {int avg_flags; int /*<<< orphan*/  avg_res; } ;

/* Variables and functions */
 int ALTERA_AVALON_FLAG_MMAP_EXEC ; 
 int ALTERA_AVALON_FLAG_MMAP_READ ; 
 int ALTERA_AVALON_FLAG_MMAP_WRITE ; 
 int EACCES ; 
 int ENODEV ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VM_MEMATTR_UNCACHEABLE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 scalar_t__ rman_get_size (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static int
altera_avgen_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr)
{
	struct altera_avgen_softc *sc;

	sc = dev->si_drv1;
	if (nprot & VM_PROT_READ) {
		if ((sc->avg_flags & ALTERA_AVALON_FLAG_MMAP_READ) == 0)
			return (EACCES);
	}
	if (nprot & VM_PROT_WRITE) {
		if ((sc->avg_flags & ALTERA_AVALON_FLAG_MMAP_WRITE) == 0)
			return (EACCES);
	}
	if (nprot & VM_PROT_EXECUTE) {
		if ((sc->avg_flags & ALTERA_AVALON_FLAG_MMAP_EXEC) == 0)
			return (EACCES);
	}
	if (trunc_page(offset) == offset &&
	    offset + PAGE_SIZE > offset &&
	    rman_get_size(sc->avg_res) >= offset + PAGE_SIZE) {
		*paddr = rman_get_start(sc->avg_res) + offset;
		*memattr = VM_MEMATTR_UNCACHEABLE;
	} else
		return (ENODEV);
	return (0);
}