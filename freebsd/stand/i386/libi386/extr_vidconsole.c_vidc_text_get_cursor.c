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
typedef  int uint16_t ;
typedef  int teken_unit_t ;

/* Variables and functions */
 int TEXT_COLS ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_HIGH ; 
 int /*<<< orphan*/  VGA_CRTC_CURSOR_LOC_LOW ; 
 int /*<<< orphan*/  VGA_REG_BASE ; 
 int vga_get_crtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vidc_text_get_cursor(teken_unit_t *row, teken_unit_t *col)
{
	uint16_t addr;

	addr = (vga_get_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_LOC_HIGH) << 8) +
	    vga_get_crtc(VGA_REG_BASE, VGA_CRTC_CURSOR_LOC_LOW);

	*row = addr / TEXT_COLS;
	*col = addr % TEXT_COLS;
}