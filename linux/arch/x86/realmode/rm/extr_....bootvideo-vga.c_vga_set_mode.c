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
struct mode_info {int mode; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
#define  VIDEO_80x25 134 
#define  VIDEO_80x28 133 
#define  VIDEO_80x30 132 
#define  VIDEO_80x34 131 
#define  VIDEO_80x43 130 
#define  VIDEO_80x60 129 
#define  VIDEO_8POINT 128 
 int /*<<< orphan*/  force_x ; 
 int /*<<< orphan*/  force_y ; 
 int /*<<< orphan*/  vga_set_14font () ; 
 int /*<<< orphan*/  vga_set_80x30 () ; 
 int /*<<< orphan*/  vga_set_80x34 () ; 
 int /*<<< orphan*/  vga_set_80x43 () ; 
 int /*<<< orphan*/  vga_set_80x60 () ; 
 int /*<<< orphan*/  vga_set_8font () ; 
 int /*<<< orphan*/  vga_set_basic_mode () ; 

__attribute__((used)) static int vga_set_mode(struct mode_info *mode)
{
	/* Set the basic mode */
	vga_set_basic_mode();

	/* Override a possibly broken BIOS */
	force_x = mode->x;
	force_y = mode->y;

	switch (mode->mode) {
	case VIDEO_80x25:
		break;
	case VIDEO_8POINT:
		vga_set_8font();
		break;
	case VIDEO_80x43:
		vga_set_80x43();
		break;
	case VIDEO_80x28:
		vga_set_14font();
		break;
	case VIDEO_80x30:
		vga_set_80x30();
		break;
	case VIDEO_80x34:
		vga_set_80x34();
		break;
	case VIDEO_80x60:
		vga_set_80x60();
		break;
	}

	return 0;
}