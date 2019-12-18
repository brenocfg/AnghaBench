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
typedef  int vm_ooffset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int /*<<< orphan*/  video_adapter_t ;
struct bcmsc_softc {int stride; int height; scalar_t__ fb_paddr; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int
bcmfb_mmap(video_adapter_t *adp, vm_ooffset_t offset, vm_paddr_t *paddr,
    int prot, vm_memattr_t *memattr)
{
	struct bcmsc_softc *sc;

	sc = (struct bcmsc_softc *)adp;

	/*
	 * This might be a legacy VGA mem request: if so, just point it at the
	 * framebuffer, since it shouldn't be touched
	 */
	if (offset < sc->stride*sc->height) {
		*paddr = sc->fb_paddr + offset;
		return (0);
	}

	return (EINVAL);
}