#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct pci_fbuf_softc {scalar_t__ gc_width; scalar_t__ gc_height; TYPE_1__ memregs; int /*<<< orphan*/  vgasc; TYPE_2__* gc_image; scalar_t__ vga_full; } ;
struct bhyvegc {int dummy; } ;
struct TYPE_4__ {scalar_t__ vgamode; } ;

/* Variables and functions */
 int /*<<< orphan*/  bhyvegc_resize (struct bhyvegc*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vga_render (struct bhyvegc*,int /*<<< orphan*/ ) ; 

void
pci_fbuf_render(struct bhyvegc *gc, void *arg)
{
	struct pci_fbuf_softc *sc;

	sc = arg;

	if (sc->vga_full && sc->gc_image->vgamode) {
		/* TODO: mode switching to vga and vesa should use the special
		 *      EFI-bhyve protocol port.
		 */
		vga_render(gc, sc->vgasc);
		return;
	}
	if (sc->gc_width != sc->memregs.width ||
	    sc->gc_height != sc->memregs.height) {
		bhyvegc_resize(gc, sc->memregs.width, sc->memregs.height);
		sc->gc_width = sc->memregs.width;
		sc->gc_height = sc->memregs.height;
	}

	return;
}