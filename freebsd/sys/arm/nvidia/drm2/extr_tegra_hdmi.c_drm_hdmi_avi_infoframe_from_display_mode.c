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
struct hdmi_avi_infoframe {int pixel_repeat; scalar_t__ video_code; scalar_t__ picture_aspect; int /*<<< orphan*/  scan_mode; int /*<<< orphan*/  active_aspect; } ;
struct drm_display_mode {int flags; scalar_t__ picture_aspect_ratio; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_DBLCLK ; 
 int EINVAL ; 
 int /*<<< orphan*/  HDMI_ACTIVE_ASPECT_PICTURE ; 
 scalar_t__ HDMI_PICTURE_ASPECT_16_9 ; 
 scalar_t__ HDMI_PICTURE_ASPECT_4_3 ; 
 scalar_t__ HDMI_PICTURE_ASPECT_NONE ; 
 int /*<<< orphan*/  HDMI_SCAN_MODE_UNDERSCAN ; 
 scalar_t__ drm_get_cea_aspect_ratio (scalar_t__) ; 
 scalar_t__ drm_match_cea_mode (struct drm_display_mode*) ; 
 int hdmi_avi_infoframe_init (struct hdmi_avi_infoframe*) ; 

__attribute__((used)) static int
drm_hdmi_avi_infoframe_from_display_mode(struct hdmi_avi_infoframe *frame,
    struct drm_display_mode *mode)
{
	int rv;

	if (!frame || !mode)
		return -EINVAL;

	rv = hdmi_avi_infoframe_init(frame);
	if (rv < 0)
		return rv;

	if (mode->flags & DRM_MODE_FLAG_DBLCLK)
		frame->pixel_repeat = 1;

	frame->video_code = drm_match_cea_mode(mode);

	frame->picture_aspect = HDMI_PICTURE_ASPECT_NONE;
#ifdef FREEBSD_NOTYET
	/*
	 * Populate picture aspect ratio from either
	 * user input (if specified) or from the CEA mode list.
	*/
	if (mode->picture_aspect_ratio == HDMI_PICTURE_ASPECT_4_3 ||
	    mode->picture_aspect_ratio == HDMI_PICTURE_ASPECT_16_9)
		frame->picture_aspect = mode->picture_aspect_ratio;
	else if (frame->video_code > 0)
		frame->picture_aspect = drm_get_cea_aspect_ratio(
		    frame->video_code);
#endif

	frame->active_aspect = HDMI_ACTIVE_ASPECT_PICTURE;
	frame->scan_mode = HDMI_SCAN_MODE_UNDERSCAN;

	return 0;
}