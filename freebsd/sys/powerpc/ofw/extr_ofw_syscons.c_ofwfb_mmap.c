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
typedef  int vm_paddr_t ;
typedef  int vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct ofwfb_softc {int sc_num_pciaddrs; int sc_stride; int sc_height; int sc_addr; TYPE_1__* sc_pciaddrs; } ;
struct TYPE_2__ {int phys_lo; int size_lo; int phys_hi; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int OFW_PCI_PHYS_HI_PREFETCHABLE ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 scalar_t__ ofwfb_ignore_mmap_checks ; 

__attribute__((used)) static int
ofwfb_mmap(video_adapter_t *adp, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	struct ofwfb_softc *sc;
	int i;

	sc = (struct ofwfb_softc *)adp;

	/*
	 * Make sure the requested address lies within the PCI device's
	 * assigned addrs
	 */
	for (i = 0; i < sc->sc_num_pciaddrs; i++)
	  if (offset >= sc->sc_pciaddrs[i].phys_lo &&
	    offset < (sc->sc_pciaddrs[i].phys_lo + sc->sc_pciaddrs[i].size_lo))
		{
			/*
			 * If this is a prefetchable BAR, we can (and should)
			 * enable write-combining.
			 */
			if (sc->sc_pciaddrs[i].phys_hi &
			    OFW_PCI_PHYS_HI_PREFETCHABLE)
				*memattr = VM_MEMATTR_WRITE_COMBINING;

			*paddr = offset;
			return (0);
		}

	/*
	 * Hack for Radeon...
	 */
	if (ofwfb_ignore_mmap_checks) {
		*paddr = offset;
		return (0);
	}

	/*
	 * This might be a legacy VGA mem request: if so, just point it at the
	 * framebuffer, since it shouldn't be touched
	 */
	if (offset < sc->sc_stride*sc->sc_height) {
		*paddr = sc->sc_addr + offset;
		return (0);
	}

	/*
	 * Error if we didn't have a better idea.
	 */
	if (sc->sc_num_pciaddrs == 0)
		return (ENOMEM);

	return (EINVAL);
}