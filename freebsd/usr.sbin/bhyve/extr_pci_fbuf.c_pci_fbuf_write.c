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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vmctx {int dummy; } ;
struct TYPE_3__ {scalar_t__ width; scalar_t__ height; } ;
struct pci_fbuf_softc {TYPE_2__* gc_image; TYPE_1__ memregs; scalar_t__ gc_height; scalar_t__ gc_width; } ;
struct pci_devinst {struct pci_fbuf_softc* pi_arg; } ;
struct TYPE_4__ {int vgamode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INFO ; 
 int /*<<< orphan*/  DEBUG_VERBOSE ; 
 scalar_t__ DMEMSZ ; 
 int /*<<< orphan*/  DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static void
pci_fbuf_write(struct vmctx *ctx, int vcpu, struct pci_devinst *pi,
	       int baridx, uint64_t offset, int size, uint64_t value)
{
	struct pci_fbuf_softc *sc;
	uint8_t *p;

	assert(baridx == 0);

	sc = pi->pi_arg;

	DPRINTF(DEBUG_VERBOSE,
	    ("fbuf wr: offset 0x%lx, size: %d, value: 0x%lx\n",
	    offset, size, value));

	if (offset + size > DMEMSZ) {
		printf("fbuf: write too large, offset %ld size %d\n",
		       offset, size);
		return;
	}

	p = (uint8_t *)&sc->memregs + offset;

	switch (size) {
	case 1:
		*p = value;
		break;
	case 2:
		*(uint16_t *)p = value;
		break;
	case 4:
		*(uint32_t *)p = value;
		break;
	case 8:
		*(uint64_t *)p = value;
		break;
	default:
		printf("fbuf: write unknown size %d\n", size);
		break;
	}

	if (!sc->gc_image->vgamode && sc->memregs.width == 0 &&
	    sc->memregs.height == 0) {
		DPRINTF(DEBUG_INFO, ("switching to VGA mode\r\n"));
		sc->gc_image->vgamode = 1;
		sc->gc_width = 0;
		sc->gc_height = 0;
	} else if (sc->gc_image->vgamode && sc->memregs.width != 0 &&
	    sc->memregs.height != 0) {
		DPRINTF(DEBUG_INFO, ("switching to VESA mode\r\n"));
		sc->gc_image->vgamode = 0;
	}
}