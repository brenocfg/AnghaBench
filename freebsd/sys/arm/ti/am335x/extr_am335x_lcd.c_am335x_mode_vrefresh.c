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
typedef  int uint32_t ;
struct videomode {int dot_clock; int htotal; int vtotal; int flags; } ;

/* Variables and functions */
 int VID_DBLSCAN ; 
 int VID_INTERLACE ; 

__attribute__((used)) static uint32_t
am335x_mode_vrefresh(const struct videomode *mode)
{
	uint32_t refresh;

	/* Calculate vertical refresh rate */
        refresh = (mode->dot_clock * 1000 / mode->htotal);
	refresh = (refresh + mode->vtotal / 2) / mode->vtotal;

	if (mode->flags & VID_INTERLACE)
		refresh *= 2;
	if (mode->flags & VID_DBLSCAN)
		refresh /= 2;

	return refresh;
}