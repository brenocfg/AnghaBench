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
struct edid {int revision; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int drm_mode_hsync (struct drm_display_mode const*) ; 

__attribute__((used)) static bool
mode_in_hsync_range(const struct drm_display_mode *mode,
		    struct edid *edid, u8 *t)
{
	int hsync, hmin, hmax;

	hmin = t[7];
	if (edid->revision >= 4)
	    hmin += ((t[4] & 0x04) ? 255 : 0);
	hmax = t[8];
	if (edid->revision >= 4)
	    hmax += ((t[4] & 0x08) ? 255 : 0);
	hsync = drm_mode_hsync(mode);

	return (hsync <= hmax && hsync >= hmin);
}