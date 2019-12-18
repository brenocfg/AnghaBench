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
typedef  int /*<<< orphan*/  win ;
struct TYPE_2__ {int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct tegra_fb {TYPE_1__ drm_fb; } ;
struct dc_window {int src_x; int src_y; int dst_x; int dst_y; int /*<<< orphan*/  dst_h; int /*<<< orphan*/  dst_w; int /*<<< orphan*/  src_h; int /*<<< orphan*/  src_w; } ;
struct dc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_WARNING (char*,int /*<<< orphan*/ ) ; 
 int dc_parse_drm_format (struct tegra_fb*,struct dc_window*) ; 
 int /*<<< orphan*/  dc_setup_window (struct dc_softc*,int /*<<< orphan*/ ,struct dc_window*) ; 
 int /*<<< orphan*/  memset (struct dc_window*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
dc_set_base(struct dc_softc *sc, int x, int y, struct tegra_fb *fb)
{
	struct dc_window win;
	int rv;

	memset(&win, 0, sizeof(win));
	win.src_x = x;
	win.src_y = y;
	win.src_w = fb->drm_fb.width;
	win.src_h = fb->drm_fb.height;
	win.dst_x = x;
	win.dst_y = y;
	win.dst_w = fb->drm_fb.width;
	win.dst_h = fb->drm_fb.height;

	rv = dc_parse_drm_format(fb, &win);
	if (rv != 0) {
		DRM_WARNING("unsupported pixel format %d\n",
		    fb->drm_fb.pixel_format);
		return (rv);
	}
	dc_setup_window(sc, 0, &win);

	return (0);
}