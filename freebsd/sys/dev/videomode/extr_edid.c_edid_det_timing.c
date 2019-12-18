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
struct videomode {int dot_clock; unsigned int hdisplay; unsigned int htotal; unsigned int hsync_start; unsigned int hsync_end; unsigned int vdisplay; unsigned int vtotal; unsigned int vsync_start; unsigned int vsync_end; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EDID_DET_TIMING_DOT_CLOCK (int*) ; 
 int EDID_DET_TIMING_FLAGS (int*) ; 
 int EDID_DET_TIMING_FLAG_HSYNC_POSITIVE ; 
 int EDID_DET_TIMING_FLAG_INTERLACE ; 
 int EDID_DET_TIMING_FLAG_STEREO ; 
 int EDID_DET_TIMING_FLAG_STEREO_MODE ; 
 int EDID_DET_TIMING_FLAG_VSYNC_POSITIVE ; 
 unsigned int EDID_DET_TIMING_HACTIVE (int*) ; 
 unsigned int EDID_DET_TIMING_HBLANK (int*) ; 
 unsigned int EDID_DET_TIMING_HSYNC_OFFSET (int*) ; 
 unsigned int EDID_DET_TIMING_HSYNC_WIDTH (int*) ; 
 unsigned int EDID_DET_TIMING_VACTIVE (int*) ; 
 unsigned int EDID_DET_TIMING_VBLANK (int*) ; 
 unsigned int EDID_DET_TIMING_VSYNC_OFFSET (int*) ; 
 unsigned int EDID_DET_TIMING_VSYNC_WIDTH (int*) ; 
 int /*<<< orphan*/  VID_INTERLACE ; 
 int /*<<< orphan*/  VID_NHSYNC ; 
 int /*<<< orphan*/  VID_NVSYNC ; 
 int /*<<< orphan*/  VID_PHSYNC ; 
 int /*<<< orphan*/  VID_PVSYNC ; 

__attribute__((used)) static int
edid_det_timing(uint8_t *data, struct videomode *vmp)
{
	unsigned	hactive, hblank, hsyncwid, hsyncoff;
	unsigned	vactive, vblank, vsyncwid, vsyncoff;
	uint8_t		flags;

	flags = EDID_DET_TIMING_FLAGS(data);

	/* we don't support stereo modes (for now) */
	if (flags & (EDID_DET_TIMING_FLAG_STEREO |
		EDID_DET_TIMING_FLAG_STEREO_MODE))
		return 0;

	vmp->dot_clock = EDID_DET_TIMING_DOT_CLOCK(data) / 1000;

	hactive = EDID_DET_TIMING_HACTIVE(data);
	hblank = EDID_DET_TIMING_HBLANK(data);
	hsyncwid = EDID_DET_TIMING_HSYNC_WIDTH(data);
	hsyncoff = EDID_DET_TIMING_HSYNC_OFFSET(data);

	vactive = EDID_DET_TIMING_VACTIVE(data);
	vblank = EDID_DET_TIMING_VBLANK(data);
	vsyncwid = EDID_DET_TIMING_VSYNC_WIDTH(data);
	vsyncoff = EDID_DET_TIMING_VSYNC_OFFSET(data);
	
	/* Borders are contained within the blank areas. */

	vmp->hdisplay = hactive;
	vmp->htotal = hactive + hblank;
	vmp->hsync_start = hactive + hsyncoff;
	vmp->hsync_end = vmp->hsync_start + hsyncwid;

	vmp->vdisplay = vactive;
	vmp->vtotal = vactive + vblank;
	vmp->vsync_start = vactive + vsyncoff;
	vmp->vsync_end = vmp->vsync_start + vsyncwid;

	vmp->flags = 0;

	if (flags & EDID_DET_TIMING_FLAG_INTERLACE)
		vmp->flags |= VID_INTERLACE;
	if (flags & EDID_DET_TIMING_FLAG_HSYNC_POSITIVE)
		vmp->flags |= VID_PHSYNC;
	else
		vmp->flags |= VID_NHSYNC;

	if (flags & EDID_DET_TIMING_FLAG_VSYNC_POSITIVE)
		vmp->flags |= VID_PVSYNC;
	else
		vmp->flags |= VID_NVSYNC;

	return 1;
}