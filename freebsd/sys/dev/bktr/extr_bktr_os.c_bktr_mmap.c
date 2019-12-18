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
struct cdev {int dummy; } ;
struct bktr_softc {scalar_t__ alloc_pages; int /*<<< orphan*/  bigbuf; } ;
typedef  struct bktr_softc* bktr_ptr_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ FUNCTION (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int PROT_EXEC ; 
 int UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bktr_devclass ; 
 int /*<<< orphan*/  dev2unit (struct cdev*) ; 
 scalar_t__ devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bktr_mmap( struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int nprot, vm_memattr_t *memattr )
{
	int		unit;
	bktr_ptr_t	bktr;

	unit = UNIT(dev2unit(dev));

	if (FUNCTION(dev2unit(dev)) > 0)	/* only allow mmap on /dev/bktr[n] */
		return( -1 );

	/* Get the device data */
	bktr = (struct bktr_softc*)devclass_get_softc(bktr_devclass, unit);
	if (bktr == NULL) {
		/* the device is no longer valid/functioning */
		return (ENXIO);
	}

	if (nprot & PROT_EXEC)
		return( -1 );

	if (offset < 0)
		return( -1 );

	if (offset >= bktr->alloc_pages * PAGE_SIZE)
		return( -1 );

	*paddr = vtophys(bktr->bigbuf) + offset;
	return( 0 );
}