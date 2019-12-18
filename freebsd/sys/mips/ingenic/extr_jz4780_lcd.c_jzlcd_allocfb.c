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
struct jzlcd_softc {scalar_t__ vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  dev; int /*<<< orphan*/  fbsize; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FB_ALIGN ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VM_MEMATTR_WRITE_COMBINING ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ kmem_alloc_contig (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 

__attribute__((used)) static int
jzlcd_allocfb(struct jzlcd_softc *sc)
{
	sc->vaddr = kmem_alloc_contig(sc->fbsize, M_NOWAIT | M_ZERO, 0, ~0,
	    FB_ALIGN, 0, VM_MEMATTR_WRITE_COMBINING);
	if (sc->vaddr == 0) {
		device_printf(sc->dev, "failed to allocate FB memory\n");
		return (ENOMEM);
	}
	sc->paddr = pmap_kextract(sc->vaddr);

	return (0);
}