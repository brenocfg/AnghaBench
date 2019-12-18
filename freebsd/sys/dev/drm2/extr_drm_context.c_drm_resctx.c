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
struct drm_device {int dummy; } ;
struct drm_ctx_res {int count; int /*<<< orphan*/ * contexts; } ;
struct drm_ctx {int handle; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int DRM_RESERVED_CONTEXTS ; 
 int EFAULT ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ *,struct drm_ctx*,int) ; 
 int /*<<< orphan*/  memset (struct drm_ctx*,int /*<<< orphan*/ ,int) ; 

int drm_resctx(struct drm_device *dev, void *data,
	       struct drm_file *file_priv)
{
	struct drm_ctx_res *res = data;
	struct drm_ctx ctx;
	int i;

	if (res->count >= DRM_RESERVED_CONTEXTS) {
		memset(&ctx, 0, sizeof(ctx));
		for (i = 0; i < DRM_RESERVED_CONTEXTS; i++) {
			ctx.handle = i;
			if (copy_to_user(&res->contexts[i], &ctx, sizeof(ctx)))
				return -EFAULT;
		}
	}
	res->count = DRM_RESERVED_CONTEXTS;

	return 0;
}