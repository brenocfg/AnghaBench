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
struct edid {int revision; int features; } ;

/* Variables and functions */
 int DRM_EDID_FEATURE_DEFAULT_GTF ; 
 int LEVEL_CVT ; 
 int LEVEL_DMT ; 
 int LEVEL_GTF ; 
 int LEVEL_GTF2 ; 
 scalar_t__ drm_gtf2_hbreak (struct edid*) ; 

__attribute__((used)) static int standard_timing_level(struct edid *edid)
{
	if (edid->revision >= 2) {
		if (edid->revision >= 4 && (edid->features & DRM_EDID_FEATURE_DEFAULT_GTF))
			return LEVEL_CVT;
		if (drm_gtf2_hbreak(edid))
			return LEVEL_GTF2;
		return LEVEL_GTF;
	}
	return LEVEL_DMT;
}