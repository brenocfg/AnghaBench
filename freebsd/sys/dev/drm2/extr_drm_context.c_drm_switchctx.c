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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  last_context; } ;
struct drm_ctx {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int drm_context_switch (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_switchctx(struct drm_device *dev, void *data,
		  struct drm_file *file_priv)
{
	struct drm_ctx *ctx = data;

	DRM_DEBUG("%d\n", ctx->handle);
	return drm_context_switch(dev, dev->last_context, ctx->handle);
}