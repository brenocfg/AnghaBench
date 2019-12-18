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
struct drm_fb_helper {struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  drm_fb_helper_parse_command_line (struct drm_fb_helper*) ; 
 int drm_fb_helper_probe_connector_modes (struct drm_fb_helper*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_fb_helper_single_fb_probe (struct drm_fb_helper*,int) ; 
 int /*<<< orphan*/  drm_helper_disable_unused_functions (struct drm_device*) ; 
 int /*<<< orphan*/  drm_setup_crtcs (struct drm_fb_helper*) ; 

bool drm_fb_helper_initial_config(struct drm_fb_helper *fb_helper, int bpp_sel)
{
	struct drm_device *dev = fb_helper->dev;
	int count = 0;

	/* disable all the possible outputs/crtcs before entering KMS mode */
	drm_helper_disable_unused_functions(fb_helper->dev);

	drm_fb_helper_parse_command_line(fb_helper);

	count = drm_fb_helper_probe_connector_modes(fb_helper,
						    dev->mode_config.max_width,
						    dev->mode_config.max_height);
	/*
	 * we shouldn't end up with no modes here.
	 */
	if (count == 0)
		dev_info(fb_helper->dev->dev, "No connectors reported connected with modes\n");

	drm_setup_crtcs(fb_helper);

	return drm_fb_helper_single_fb_probe(fb_helper, bpp_sel);
}