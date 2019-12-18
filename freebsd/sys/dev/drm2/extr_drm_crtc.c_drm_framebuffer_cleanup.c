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
struct drm_framebuffer {int /*<<< orphan*/  head; int /*<<< orphan*/  base; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_fb; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mode_object_put (struct drm_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void drm_framebuffer_cleanup(struct drm_framebuffer *fb)
{
	struct drm_device *dev = fb->dev;
	/*
	 * This could be moved to drm_framebuffer_remove(), but for
	 * debugging is nice to keep around the list of fb's that are
	 * no longer associated w/ a drm_file but are not unreferenced
	 * yet.  (i915 and omapdrm have debugfs files which will show
	 * this.)
	 */
	drm_mode_object_put(dev, &fb->base);
	list_del(&fb->head);
	dev->mode_config.num_fb--;
}