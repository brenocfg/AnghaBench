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
struct drm_framebuffer_funcs {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/  head; struct drm_framebuffer_funcs const* funcs; struct drm_device* dev; int /*<<< orphan*/  base; int /*<<< orphan*/  refcount; } ;
struct TYPE_2__ {int /*<<< orphan*/  fb_list; int /*<<< orphan*/  num_fb; } ;
struct drm_device {TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_OBJECT_FB ; 
 int drm_mode_object_get (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_init (int /*<<< orphan*/ *,int) ; 

int drm_framebuffer_init(struct drm_device *dev, struct drm_framebuffer *fb,
			 const struct drm_framebuffer_funcs *funcs)
{
	int ret;

	refcount_init(&fb->refcount, 1);

	ret = drm_mode_object_get(dev, &fb->base, DRM_MODE_OBJECT_FB);
	if (ret)
		return ret;

	fb->dev = dev;
	fb->funcs = funcs;
	dev->mode_config.num_fb++;
	list_add(&fb->head, &dev->mode_config.fb_list);

	return 0;
}