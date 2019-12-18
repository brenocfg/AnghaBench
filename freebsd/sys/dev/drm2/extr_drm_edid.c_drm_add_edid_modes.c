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
struct edid {int features; } ;
struct drm_connector {int /*<<< orphan*/  display_info; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DRM_EDID_FEATURE_DEFAULT_GTF ; 
 int EDID_QUIRK_PREFER_LARGE_60 ; 
 int EDID_QUIRK_PREFER_LARGE_75 ; 
 scalar_t__ add_cea_modes (struct drm_connector*,struct edid*) ; 
 scalar_t__ add_cvt_modes (struct drm_connector*,struct edid*) ; 
 scalar_t__ add_detailed_modes (struct drm_connector*,struct edid*,int) ; 
 scalar_t__ add_established_modes (struct drm_connector*,struct edid*) ; 
 scalar_t__ add_inferred_modes (struct drm_connector*,struct edid*) ; 
 scalar_t__ add_standard_modes (struct drm_connector*,struct edid*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_add_display_info (struct edid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_edid_is_valid (struct edid*) ; 
 int /*<<< orphan*/  drm_get_connector_name (struct drm_connector*) ; 
 int /*<<< orphan*/  edid_fixup_preferred (struct drm_connector*,int) ; 
 int edid_get_quirks (struct edid*) ; 

int drm_add_edid_modes(struct drm_connector *connector, struct edid *edid)
{
	int num_modes = 0;
	u32 quirks;

	if (edid == NULL) {
		return 0;
	}
	if (!drm_edid_is_valid(edid)) {
		dev_warn(connector->dev->dev, "%s: EDID invalid.\n",
			 drm_get_connector_name(connector));
		return 0;
	}

	quirks = edid_get_quirks(edid);

	/*
	 * EDID spec says modes should be preferred in this order:
	 * - preferred detailed mode
	 * - other detailed modes from base block
	 * - detailed modes from extension blocks
	 * - CVT 3-byte code modes
	 * - standard timing codes
	 * - established timing codes
	 * - modes inferred from GTF or CVT range information
	 *
	 * We get this pretty much right.
	 *
	 * XXX order for additional mode types in extension blocks?
	 */
	num_modes += add_detailed_modes(connector, edid, quirks);
	num_modes += add_cvt_modes(connector, edid);
	num_modes += add_standard_modes(connector, edid);
	num_modes += add_established_modes(connector, edid);
	if (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF)
		num_modes += add_inferred_modes(connector, edid);
	num_modes += add_cea_modes(connector, edid);

	if (quirks & (EDID_QUIRK_PREFER_LARGE_60 | EDID_QUIRK_PREFER_LARGE_75))
		edid_fixup_preferred(connector, quirks);

	drm_add_display_info(edid, &connector->display_info);

	return num_modes;
}