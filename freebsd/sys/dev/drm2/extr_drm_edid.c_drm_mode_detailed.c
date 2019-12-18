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
typedef  int u32 ;
struct edid {int width_cm; int height_cm; } ;
struct drm_display_mode {int clock; unsigned int hdisplay; unsigned int hsync_start; unsigned int hsync_end; unsigned int htotal; unsigned int vdisplay; unsigned int vsync_start; unsigned int vsync_end; unsigned int vtotal; int width_mm; int height_mm; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  type; int /*<<< orphan*/  flags; } ;
struct drm_device {int dummy; } ;
struct detailed_pixel_timing {int hactive_hblank_hi; int hactive_lo; int vactive_vblank_hi; int vactive_lo; int hblank_lo; int vblank_lo; int hsync_vsync_offset_pulse_width_hi; int hsync_offset_lo; int hsync_pulse_width_lo; int vsync_offset_pulse_width_lo; int misc; int width_mm_lo; int width_height_mm_hi; int height_mm_lo; } ;
struct TYPE_2__ {struct detailed_pixel_timing pixel_data; } ;
struct detailed_timing {int /*<<< orphan*/  pixel_clock; TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int DRM_EDID_PT_HSYNC_POSITIVE ; 
 int DRM_EDID_PT_SEPARATE_SYNC ; 
 int DRM_EDID_PT_STEREO ; 
 int DRM_EDID_PT_VSYNC_POSITIVE ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_NVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PHSYNC ; 
 int /*<<< orphan*/  DRM_MODE_FLAG_PVSYNC ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int EDID_QUIRK_135_CLOCK_TOO_HIGH ; 
 int EDID_QUIRK_DETAILED_IN_CM ; 
 int EDID_QUIRK_DETAILED_SYNC_PP ; 
 int EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE ; 
 int EDID_QUIRK_FORCE_REDUCED_BLANKING ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 struct drm_display_mode* drm_cvt_mode (struct drm_device*,unsigned int,unsigned int,int,int,int,int) ; 
 struct drm_display_mode* drm_mode_create (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_do_interlace_quirk (struct drm_display_mode*,struct detailed_pixel_timing*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_vrefresh (struct drm_display_mode*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static struct drm_display_mode *drm_mode_detailed(struct drm_device *dev,
						  struct edid *edid,
						  struct detailed_timing *timing,
						  u32 quirks)
{
	struct drm_display_mode *mode;
	struct detailed_pixel_timing *pt = &timing->data.pixel_data;
	unsigned hactive = (pt->hactive_hblank_hi & 0xf0) << 4 | pt->hactive_lo;
	unsigned vactive = (pt->vactive_vblank_hi & 0xf0) << 4 | pt->vactive_lo;
	unsigned hblank = (pt->hactive_hblank_hi & 0xf) << 8 | pt->hblank_lo;
	unsigned vblank = (pt->vactive_vblank_hi & 0xf) << 8 | pt->vblank_lo;
	unsigned hsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc0) << 2 | pt->hsync_offset_lo;
	unsigned hsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x30) << 4 | pt->hsync_pulse_width_lo;
	unsigned vsync_offset = (pt->hsync_vsync_offset_pulse_width_hi & 0xc) << 2 | pt->vsync_offset_pulse_width_lo >> 4;
	unsigned vsync_pulse_width = (pt->hsync_vsync_offset_pulse_width_hi & 0x3) << 4 | (pt->vsync_offset_pulse_width_lo & 0xf);

	/* ignore tiny modes */
	if (hactive < 64 || vactive < 64)
		return NULL;

	if (pt->misc & DRM_EDID_PT_STEREO) {
		printf("stereo mode not supported\n");
		return NULL;
	}
	if (!(pt->misc & DRM_EDID_PT_SEPARATE_SYNC)) {
		printf("composite sync not supported\n");
	}

	/* it is incorrect if hsync/vsync width is zero */
	if (!hsync_pulse_width || !vsync_pulse_width) {
		DRM_DEBUG_KMS("Incorrect Detailed timing. "
				"Wrong Hsync/Vsync pulse width\n");
		return NULL;
	}

	if (quirks & EDID_QUIRK_FORCE_REDUCED_BLANKING) {
		mode = drm_cvt_mode(dev, hactive, vactive, 60, true, false, false);
		if (!mode)
			return NULL;

		goto set_size;
	}

	mode = drm_mode_create(dev);
	if (!mode)
		return NULL;

	if (quirks & EDID_QUIRK_135_CLOCK_TOO_HIGH)
		timing->pixel_clock = cpu_to_le16(1088);

	mode->clock = le16_to_cpu(timing->pixel_clock) * 10;

	mode->hdisplay = hactive;
	mode->hsync_start = mode->hdisplay + hsync_offset;
	mode->hsync_end = mode->hsync_start + hsync_pulse_width;
	mode->htotal = mode->hdisplay + hblank;

	mode->vdisplay = vactive;
	mode->vsync_start = mode->vdisplay + vsync_offset;
	mode->vsync_end = mode->vsync_start + vsync_pulse_width;
	mode->vtotal = mode->vdisplay + vblank;

	/* Some EDIDs have bogus h/vtotal values */
	if (mode->hsync_end > mode->htotal)
		mode->htotal = mode->hsync_end + 1;
	if (mode->vsync_end > mode->vtotal)
		mode->vtotal = mode->vsync_end + 1;

	drm_mode_do_interlace_quirk(mode, pt);

	if (quirks & EDID_QUIRK_DETAILED_SYNC_PP) {
		pt->misc |= DRM_EDID_PT_HSYNC_POSITIVE | DRM_EDID_PT_VSYNC_POSITIVE;
	}

	mode->flags |= (pt->misc & DRM_EDID_PT_HSYNC_POSITIVE) ?
		DRM_MODE_FLAG_PHSYNC : DRM_MODE_FLAG_NHSYNC;
	mode->flags |= (pt->misc & DRM_EDID_PT_VSYNC_POSITIVE) ?
		DRM_MODE_FLAG_PVSYNC : DRM_MODE_FLAG_NVSYNC;

set_size:
	mode->width_mm = pt->width_mm_lo | (pt->width_height_mm_hi & 0xf0) << 4;
	mode->height_mm = pt->height_mm_lo | (pt->width_height_mm_hi & 0xf) << 8;

	if (quirks & EDID_QUIRK_DETAILED_IN_CM) {
		mode->width_mm *= 10;
		mode->height_mm *= 10;
	}

	if (quirks & EDID_QUIRK_DETAILED_USE_MAXIMUM_SIZE) {
		mode->width_mm = edid->width_cm * 10;
		mode->height_mm = edid->height_cm * 10;
	}

	mode->type = DRM_MODE_TYPE_DRIVER;
	mode->vrefresh = drm_mode_vrefresh(mode);
	drm_mode_set_name(mode);

	return mode;
}