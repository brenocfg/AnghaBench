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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct vmctx {int dummy; } ;
struct TYPE_2__ {int gc_misc_mm; int gc_latch0; int gc_latch1; int gc_latch2; int gc_latch3; int gc_read_map_sel; scalar_t__ gc_mode_oe; scalar_t__ gc_mode_rm; } ;
struct vga_softc {int* vga_ram; TYPE_1__ vga_gc; } ;

/* Variables and functions */
 int KB ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
vga_mem_rd_handler(struct vmctx *ctx, uint64_t addr, void *arg1)
{
	struct vga_softc *sc = arg1;
	uint8_t map_sel;
	int offset;

	offset = addr;
	switch (sc->vga_gc.gc_misc_mm) {
	case 0x0:
		/*
		 * extended mode: base 0xa0000 size 128k
		 */
		offset -=0xa0000;
		offset &= (128 * KB - 1);
		break;
	case 0x1:
		/*
		 * EGA/VGA mode: base 0xa0000 size 64k
		 */
		offset -=0xa0000;
		offset &= (64 * KB - 1);
		break;
	case 0x2:
		/*
		 * monochrome text mode: base 0xb0000 size 32kb
		 */
		assert(0);
	case 0x3:
		/*
		 * color text mode and CGA: base 0xb8000 size 32kb
		 */
		offset -=0xb8000;
		offset &= (32 * KB - 1);
		break;
	}

	/* Fill latches. */
	sc->vga_gc.gc_latch0 = sc->vga_ram[offset + 0*64*KB];
	sc->vga_gc.gc_latch1 = sc->vga_ram[offset + 1*64*KB];
	sc->vga_gc.gc_latch2 = sc->vga_ram[offset + 2*64*KB];
	sc->vga_gc.gc_latch3 = sc->vga_ram[offset + 3*64*KB];

	if (sc->vga_gc.gc_mode_rm) {
		/* read mode 1 */
		assert(0);
	}

	map_sel = sc->vga_gc.gc_read_map_sel;
	if (sc->vga_gc.gc_mode_oe) {
		map_sel |= (offset & 1);
		offset &= ~1;
	}

	/* read mode 0: return the byte from the selected plane. */
	offset += map_sel * 64*KB;

	return (sc->vga_ram[offset]);
}