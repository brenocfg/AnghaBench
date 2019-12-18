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
struct TYPE_2__ {int /*<<< orphan*/  pixel_format; } ;
struct tegra_fb {int nplanes; struct tegra_bo** planes; TYPE_1__ drm_fb; } ;
struct tegra_bo {int dummy; } ;

/* Variables and functions */
 int drm_format_num_planes (int /*<<< orphan*/ ) ; 

struct tegra_bo *
tegra_fb_get_plane(struct tegra_fb *fb, int idx)
{

	if (idx >= drm_format_num_planes(fb->drm_fb.pixel_format))
		return (NULL);
	if (idx >= fb->nplanes)
		return (NULL);
	return (fb->planes[idx]);
}