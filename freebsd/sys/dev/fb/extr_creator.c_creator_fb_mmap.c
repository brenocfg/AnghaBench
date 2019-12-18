#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
struct creator_softc {scalar_t__ sc_reg_size; scalar_t__* sc_bh; } ;
struct cdev {struct creator_softc* si_drv1; } ;
struct TYPE_2__ {scalar_t__ virt; scalar_t__ size; scalar_t__ phys; } ;

/* Variables and functions */
 int CREATOR_FB_MAP_SIZE ; 
 int EINVAL ; 
 TYPE_1__* creator_fb_map ; 

__attribute__((used)) static int
creator_fb_mmap(struct cdev *dev, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	struct creator_softc *sc;
	int i;

	/*
	 * NB: This is a special implementation based on the /dev/fb
	 * requirements of the XFree86/X.Org sunffb(4).
	 */
	sc = dev->si_drv1;
	for (i = 0; i < CREATOR_FB_MAP_SIZE; i++) {
		if (offset >= creator_fb_map[i].virt &&
		    offset < creator_fb_map[i].virt + creator_fb_map[i].size) {
			offset += creator_fb_map[i].phys -
			    creator_fb_map[i].virt;
			if (offset >= sc->sc_reg_size)
				return (EINVAL);
			*paddr = sc->sc_bh[0] + offset;
			return (0);
		}
	}
	return (EINVAL);
}