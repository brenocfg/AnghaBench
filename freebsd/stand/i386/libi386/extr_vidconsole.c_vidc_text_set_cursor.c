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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int teken_unit_t ;

/* Variables and functions */
 int TEXT_COLS ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_END ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_HIGH ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_LOW ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_START ; 
 int /*<<< orphan*/  VGA_CRTC_MAX_SCAN_LINE ; 
 int /*<<< orphan*/  VGA_REG_BASE ; 
 int vga_get_crtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_set_crtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vidc_text_set_cursor(teken_unit_t row, teken_unit_t col, bool visible)
{
        uint16_t addr;
        uint8_t msl, s, e;

        msl = vga_get_crtc(VGA_REG_BASE, VGA_CRTC_MAX_SCAN_LINE) & 0x1f;
        s = vga_get_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_START) & 0xC0;
        e = vga_get_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_END);

        if (visible == true) {
                addr = row * TEXT_COLS + col;
                vga_set_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_LOC_HIGH, addr >> 8);
                vga_set_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_LOC_LOW,
		    addr & 0xff);
                e = msl;
        } else {
                s |= (1<<5);
        }
        vga_set_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_START, s);
        vga_set_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_END, e);
}