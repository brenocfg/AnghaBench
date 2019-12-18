#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dac_palette_rgb; } ;
struct TYPE_7__ {int* atc_palette; } ;
struct TYPE_6__ {int seq_cm_dots; int seq_mm; int seq_cmap_pri_off; int seq_cmap_sec_off; } ;
struct TYPE_5__ {int crtc_start_addr; int crtc_cursor_loc; int crtc_cursor_start; int crtc_cursor_end; scalar_t__ crtc_cursor_on; } ;
struct vga_softc {int gc_width; int* vga_ram; TYPE_4__ vga_dac; TYPE_3__ vga_atc; TYPE_2__ vga_seq; TYPE_1__ vga_crtc; } ;

/* Variables and functions */
 int CRTC_CE_CE ; 
 int CRTC_CS_CS ; 
 int KB ; 
 int SEQ_MM_EM ; 

__attribute__((used)) static uint32_t
vga_get_text_pixel(struct vga_softc *sc, int x, int y)
{
	int dots, offset, bit, font_offset;
	uint8_t ch, attr, font;
	uint8_t idx;

	dots = sc->vga_seq.seq_cm_dots;

	offset = 2 * sc->vga_crtc.crtc_start_addr;
	offset += (y / 16 * sc->gc_width / dots) * 2 + (x / dots) * 2;

	bit = 7 - (x % dots > 7 ? 7 : x % dots);

	ch = sc->vga_ram[offset + 0 * 64*KB];
	attr = sc->vga_ram[offset + 1 * 64*KB];

	if (sc->vga_crtc.crtc_cursor_on &&
	    (offset == (sc->vga_crtc.crtc_cursor_loc * 2)) &&
	    ((y % 16) >= (sc->vga_crtc.crtc_cursor_start & CRTC_CS_CS)) &&
	    ((y % 16) <= (sc->vga_crtc.crtc_cursor_end & CRTC_CE_CE))) {
		idx = sc->vga_atc.atc_palette[attr & 0xf];
		return (sc->vga_dac.dac_palette_rgb[idx]);
	}

	if ((sc->vga_seq.seq_mm & SEQ_MM_EM) &&
	    sc->vga_seq.seq_cmap_pri_off != sc->vga_seq.seq_cmap_sec_off) {
		if (attr & 0x8)
			font_offset = sc->vga_seq.seq_cmap_pri_off +
				(ch << 5) + y % 16;
		else
			font_offset = sc->vga_seq.seq_cmap_sec_off +
				(ch << 5) + y % 16;
		attr &= ~0x8;
	} else {
		font_offset = (ch << 5) + y % 16;
	}

	font = sc->vga_ram[font_offset + 2 * 64*KB];

	if (font & (1 << bit))
		idx = sc->vga_atc.atc_palette[attr & 0xf];
	else
		idx = sc->vga_atc.atc_palette[attr >> 4];

	return (sc->vga_dac.dac_palette_rgb[idx]);
}