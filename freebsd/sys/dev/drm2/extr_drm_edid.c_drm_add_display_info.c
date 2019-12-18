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
typedef  int u8 ;
struct edid {int width_cm; int height_cm; int revision; int input; int features; } ;
struct drm_display_info {int width_mm; int height_mm; int bpc; int cea_rev; int /*<<< orphan*/  color_formats; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_COLOR_FORMAT_RGB444 ; 
 int /*<<< orphan*/  DRM_COLOR_FORMAT_YCRCB422 ; 
 int /*<<< orphan*/  DRM_COLOR_FORMAT_YCRCB444 ; 
#define  DRM_EDID_DIGITAL_DEPTH_10 134 
#define  DRM_EDID_DIGITAL_DEPTH_12 133 
#define  DRM_EDID_DIGITAL_DEPTH_14 132 
#define  DRM_EDID_DIGITAL_DEPTH_16 131 
#define  DRM_EDID_DIGITAL_DEPTH_6 130 
#define  DRM_EDID_DIGITAL_DEPTH_8 129 
 int DRM_EDID_DIGITAL_DEPTH_MASK ; 
#define  DRM_EDID_DIGITAL_DEPTH_UNDEF 128 
 int DRM_EDID_FEATURE_RGB_YCRCB422 ; 
 int DRM_EDID_FEATURE_RGB_YCRCB444 ; 
 int DRM_EDID_INPUT_DIGITAL ; 
 int EDID_CEA_YCRCB422 ; 
 int EDID_CEA_YCRCB444 ; 
 int* drm_find_cea_extension (struct edid*) ; 

__attribute__((used)) static void drm_add_display_info(struct edid *edid,
				 struct drm_display_info *info)
{
	u8 *edid_ext;

	info->width_mm = edid->width_cm * 10;
	info->height_mm = edid->height_cm * 10;

	/* driver figures it out in this case */
	info->bpc = 0;
	info->color_formats = 0;

	if (edid->revision < 3)
		return;

	if (!(edid->input & DRM_EDID_INPUT_DIGITAL))
		return;

	/* Get data from CEA blocks if present */
	edid_ext = drm_find_cea_extension(edid);
	if (edid_ext) {
		info->cea_rev = edid_ext[1];

		/* The existence of a CEA block should imply RGB support */
		info->color_formats = DRM_COLOR_FORMAT_RGB444;
		if (edid_ext[3] & EDID_CEA_YCRCB444)
			info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
		if (edid_ext[3] & EDID_CEA_YCRCB422)
			info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
	}

	/* Only defined for 1.4 with digital displays */
	if (edid->revision < 4)
		return;

	switch (edid->input & DRM_EDID_DIGITAL_DEPTH_MASK) {
	case DRM_EDID_DIGITAL_DEPTH_6:
		info->bpc = 6;
		break;
	case DRM_EDID_DIGITAL_DEPTH_8:
		info->bpc = 8;
		break;
	case DRM_EDID_DIGITAL_DEPTH_10:
		info->bpc = 10;
		break;
	case DRM_EDID_DIGITAL_DEPTH_12:
		info->bpc = 12;
		break;
	case DRM_EDID_DIGITAL_DEPTH_14:
		info->bpc = 14;
		break;
	case DRM_EDID_DIGITAL_DEPTH_16:
		info->bpc = 16;
		break;
	case DRM_EDID_DIGITAL_DEPTH_UNDEF:
	default:
		info->bpc = 0;
		break;
	}

	info->color_formats |= DRM_COLOR_FORMAT_RGB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB444)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB444;
	if (edid->features & DRM_EDID_FEATURE_RGB_YCRCB422)
		info->color_formats |= DRM_COLOR_FORMAT_YCRCB422;
}