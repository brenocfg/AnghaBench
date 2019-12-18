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
struct drm_display_mode {int hdisplay; int vdisplay; int vtotal; int htotal; int hsync_end; int hsync_start; int vsync_start; int vsync_end; int clock; int flags; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int CVT_CLOCK_STEP ; 
 int CVT_C_PRIME ; 
 int CVT_HSYNC_PERCENTAGE ; 
 int CVT_H_GRANULARITY ; 
 int CVT_MARGIN_PERCENTAGE ; 
 int CVT_MIN_VSYNC_BP ; 
 int CVT_MIN_V_BPORCH ; 
 int CVT_MIN_V_PORCH ; 
 unsigned int CVT_M_PRIME ; 
 int CVT_RB_H_BLANK ; 
 int CVT_RB_H_SYNC ; 
 int CVT_RB_MIN_VBLANK ; 
 int CVT_RB_VFPORCH ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 int DRM_MODE_FLAG_NHSYNC ; 
 int DRM_MODE_FLAG_NVSYNC ; 
 int DRM_MODE_FLAG_PHSYNC ; 
 int DRM_MODE_FLAG_PVSYNC ; 
 int HV_FACTOR ; 
 struct drm_display_mode* drm_mode_create (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_set_name (struct drm_display_mode*) ; 

struct drm_display_mode *drm_cvt_mode(struct drm_device *dev, int hdisplay,
				      int vdisplay, int vrefresh,
				      bool reduced, bool interlaced, bool margins)
{
	/* 1) top/bottom margin size (% of height) - default: 1.8, */
#define	CVT_MARGIN_PERCENTAGE		18
	/* 2) character cell horizontal granularity (pixels) - default 8 */
#define	CVT_H_GRANULARITY		8
	/* 3) Minimum vertical porch (lines) - default 3 */
#define	CVT_MIN_V_PORCH			3
	/* 4) Minimum number of vertical back porch lines - default 6 */
#define	CVT_MIN_V_BPORCH		6
	/* Pixel Clock step (kHz) */
#define CVT_CLOCK_STEP			250
	struct drm_display_mode *drm_mode;
	unsigned int vfieldrate, hperiod;
	int hdisplay_rnd, hmargin, vdisplay_rnd, vmargin, vsync;
	int interlace;

	/* allocate the drm_display_mode structure. If failure, we will
	 * return directly
	 */
	drm_mode = drm_mode_create(dev);
	if (!drm_mode)
		return NULL;

	/* the CVT default refresh rate is 60Hz */
	if (!vrefresh)
		vrefresh = 60;

	/* the required field fresh rate */
	if (interlaced)
		vfieldrate = vrefresh * 2;
	else
		vfieldrate = vrefresh;

	/* horizontal pixels */
	hdisplay_rnd = hdisplay - (hdisplay % CVT_H_GRANULARITY);

	/* determine the left&right borders */
	hmargin = 0;
	if (margins) {
		hmargin = hdisplay_rnd * CVT_MARGIN_PERCENTAGE / 1000;
		hmargin -= hmargin % CVT_H_GRANULARITY;
	}
	/* find the total active pixels */
	drm_mode->hdisplay = hdisplay_rnd + 2 * hmargin;

	/* find the number of lines per field */
	if (interlaced)
		vdisplay_rnd = vdisplay / 2;
	else
		vdisplay_rnd = vdisplay;

	/* find the top & bottom borders */
	vmargin = 0;
	if (margins)
		vmargin = vdisplay_rnd * CVT_MARGIN_PERCENTAGE / 1000;

	drm_mode->vdisplay = vdisplay + 2 * vmargin;

	/* Interlaced */
	if (interlaced)
		interlace = 1;
	else
		interlace = 0;

	/* Determine VSync Width from aspect ratio */
	if (!(vdisplay % 3) && ((vdisplay * 4 / 3) == hdisplay))
		vsync = 4;
	else if (!(vdisplay % 9) && ((vdisplay * 16 / 9) == hdisplay))
		vsync = 5;
	else if (!(vdisplay % 10) && ((vdisplay * 16 / 10) == hdisplay))
		vsync = 6;
	else if (!(vdisplay % 4) && ((vdisplay * 5 / 4) == hdisplay))
		vsync = 7;
	else if (!(vdisplay % 9) && ((vdisplay * 15 / 9) == hdisplay))
		vsync = 7;
	else /* custom */
		vsync = 10;

	if (!reduced) {
		/* simplify the GTF calculation */
		/* 4) Minimum time of vertical sync + back porch interval (µs)
		 * default 550.0
		 */
		int tmp1, tmp2;
#define CVT_MIN_VSYNC_BP	550
		/* 3) Nominal HSync width (% of line period) - default 8 */
#define CVT_HSYNC_PERCENTAGE	8
		unsigned int hblank_percentage;
		int vsyncandback_porch, vback_porch, hblank;

		/* estimated the horizontal period */
		tmp1 = HV_FACTOR * 1000000  -
				CVT_MIN_VSYNC_BP * HV_FACTOR * vfieldrate;
		tmp2 = (vdisplay_rnd + 2 * vmargin + CVT_MIN_V_PORCH) * 2 +
				interlace;
		hperiod = tmp1 * 2 / (tmp2 * vfieldrate);

		tmp1 = CVT_MIN_VSYNC_BP * HV_FACTOR / hperiod + 1;
		/* 9. Find number of lines in sync + backporch */
		if (tmp1 < (vsync + CVT_MIN_V_PORCH))
			vsyncandback_porch = vsync + CVT_MIN_V_PORCH;
		else
			vsyncandback_porch = tmp1;
		/* 10. Find number of lines in back porch */
		vback_porch = vsyncandback_porch - vsync;
		drm_mode->vtotal = vdisplay_rnd + 2 * vmargin +
				vsyncandback_porch + CVT_MIN_V_PORCH;
		/* 5) Definition of Horizontal blanking time limitation */
		/* Gradient (%/kHz) - default 600 */
#define CVT_M_FACTOR	600
		/* Offset (%) - default 40 */
#define CVT_C_FACTOR	40
		/* Blanking time scaling factor - default 128 */
#define CVT_K_FACTOR	128
		/* Scaling factor weighting - default 20 */
#define CVT_J_FACTOR	20
#define CVT_M_PRIME	(CVT_M_FACTOR * CVT_K_FACTOR / 256)
#define CVT_C_PRIME	((CVT_C_FACTOR - CVT_J_FACTOR) * CVT_K_FACTOR / 256 + \
			 CVT_J_FACTOR)
		/* 12. Find ideal blanking duty cycle from formula */
		hblank_percentage = CVT_C_PRIME * HV_FACTOR - CVT_M_PRIME *
					hperiod / 1000;
		/* 13. Blanking time */
		if (hblank_percentage < 20 * HV_FACTOR)
			hblank_percentage = 20 * HV_FACTOR;
		hblank = drm_mode->hdisplay * hblank_percentage /
			 (100 * HV_FACTOR - hblank_percentage);
		hblank -= hblank % (2 * CVT_H_GRANULARITY);
		/* 14. find the total pixes per line */
		drm_mode->htotal = drm_mode->hdisplay + hblank;
		drm_mode->hsync_end = drm_mode->hdisplay + hblank / 2;
		drm_mode->hsync_start = drm_mode->hsync_end -
			(drm_mode->htotal * CVT_HSYNC_PERCENTAGE) / 100;
		drm_mode->hsync_start += CVT_H_GRANULARITY -
			drm_mode->hsync_start % CVT_H_GRANULARITY;
		/* fill the Vsync values */
		drm_mode->vsync_start = drm_mode->vdisplay + CVT_MIN_V_PORCH;
		drm_mode->vsync_end = drm_mode->vsync_start + vsync;
	} else {
		/* Reduced blanking */
		/* Minimum vertical blanking interval time (µs)- default 460 */
#define CVT_RB_MIN_VBLANK	460
		/* Fixed number of clocks for horizontal sync */
#define CVT_RB_H_SYNC		32
		/* Fixed number of clocks for horizontal blanking */
#define CVT_RB_H_BLANK		160
		/* Fixed number of lines for vertical front porch - default 3*/
#define CVT_RB_VFPORCH		3
		int vbilines;
		int tmp1, tmp2;
		/* 8. Estimate Horizontal period. */
		tmp1 = HV_FACTOR * 1000000 -
			CVT_RB_MIN_VBLANK * HV_FACTOR * vfieldrate;
		tmp2 = vdisplay_rnd + 2 * vmargin;
		hperiod = tmp1 / (tmp2 * vfieldrate);
		/* 9. Find number of lines in vertical blanking */
		vbilines = CVT_RB_MIN_VBLANK * HV_FACTOR / hperiod + 1;
		/* 10. Check if vertical blanking is sufficient */
		if (vbilines < (CVT_RB_VFPORCH + vsync + CVT_MIN_V_BPORCH))
			vbilines = CVT_RB_VFPORCH + vsync + CVT_MIN_V_BPORCH;
		/* 11. Find total number of lines in vertical field */
		drm_mode->vtotal = vdisplay_rnd + 2 * vmargin + vbilines;
		/* 12. Find total number of pixels in a line */
		drm_mode->htotal = drm_mode->hdisplay + CVT_RB_H_BLANK;
		/* Fill in HSync values */
		drm_mode->hsync_end = drm_mode->hdisplay + CVT_RB_H_BLANK / 2;
		drm_mode->hsync_start = drm_mode->hsync_end - CVT_RB_H_SYNC;
		/* Fill in VSync values */
		drm_mode->vsync_start = drm_mode->vdisplay + CVT_RB_VFPORCH;
		drm_mode->vsync_end = drm_mode->vsync_start + vsync;
	}
	/* 15/13. Find pixel clock frequency (kHz for xf86) */
	drm_mode->clock = drm_mode->htotal * HV_FACTOR * 1000 / hperiod;
	drm_mode->clock -= drm_mode->clock % CVT_CLOCK_STEP;
	/* 18/16. Find actual vertical frame frequency */
	/* ignore - just set the mode flag for interlaced */
	if (interlaced) {
		drm_mode->vtotal *= 2;
		drm_mode->flags |= DRM_MODE_FLAG_INTERLACE;
	}
	/* Fill the mode line name */
	drm_mode_set_name(drm_mode);
	if (reduced)
		drm_mode->flags |= (DRM_MODE_FLAG_PHSYNC |
					DRM_MODE_FLAG_NVSYNC);
	else
		drm_mode->flags |= (DRM_MODE_FLAG_PVSYNC |
					DRM_MODE_FLAG_NHSYNC);

	return drm_mode;
}