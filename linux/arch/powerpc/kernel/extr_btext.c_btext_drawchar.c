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

/* Variables and functions */
 int /*<<< orphan*/  boot_text_mapped ; 
 int /*<<< orphan*/  draw_byte (char,int,scalar_t__) ; 
 scalar_t__ g_loc_X ; 
 scalar_t__ g_loc_Y ; 
 scalar_t__ g_max_loc_X ; 
 scalar_t__ g_max_loc_Y ; 
 int /*<<< orphan*/  scrollscreen () ; 

void btext_drawchar(char c)
{
	int cline = 0;
#ifdef NO_SCROLL
	int x;
#endif
	if (!boot_text_mapped)
		return;

	switch (c) {
	case '\b':
		if (g_loc_X > 0)
			--g_loc_X;
		break;
	case '\t':
		g_loc_X = (g_loc_X & -8) + 8;
		break;
	case '\r':
		g_loc_X = 0;
		break;
	case '\n':
		g_loc_X = 0;
		g_loc_Y++;
		cline = 1;
		break;
	default:
		draw_byte(c, g_loc_X++, g_loc_Y);
	}
	if (g_loc_X >= g_max_loc_X) {
		g_loc_X = 0;
		g_loc_Y++;
		cline = 1;
	}
#ifndef NO_SCROLL
	while (g_loc_Y >= g_max_loc_Y) {
		scrollscreen();
		g_loc_Y--;
	}
#else
	/* wrap around from bottom to top of screen so we don't
	   waste time scrolling each line.  -- paulus. */
	if (g_loc_Y >= g_max_loc_Y)
		g_loc_Y = 0;
	if (cline) {
		for (x = 0; x < g_max_loc_X; ++x)
			draw_byte(' ', x, g_loc_Y);
	}
#endif
}