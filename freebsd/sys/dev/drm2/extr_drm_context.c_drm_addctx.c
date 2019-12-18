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
struct drm_device {int /*<<< orphan*/  ctx_count; int /*<<< orphan*/  ctxlist; } ;
struct drm_ctx_list {int handle; int /*<<< orphan*/  head; struct drm_file* tag; } ;
struct drm_ctx {int handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,...) ; 
 int DRM_KERNEL_CONTEXT ; 
 int /*<<< orphan*/  DRM_LOCK (struct drm_device*) ; 
 int /*<<< orphan*/  DRM_MEM_CTXBITMAP ; 
 int /*<<< orphan*/  DRM_UNLOCK (struct drm_device*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 void* drm_ctxbitmap_next (struct drm_device*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct drm_ctx_list* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int drm_addctx(struct drm_device *dev, void *data,
	       struct drm_file *file_priv)
{
	struct drm_ctx_list *ctx_entry;
	struct drm_ctx *ctx = data;

	ctx->handle = drm_ctxbitmap_next(dev);
	if (ctx->handle == DRM_KERNEL_CONTEXT) {
		/* Skip kernel's context and get a new one. */
		ctx->handle = drm_ctxbitmap_next(dev);
	}
	DRM_DEBUG("%d\n", ctx->handle);
	if (ctx->handle == -1) {
		DRM_DEBUG("Not enough free contexts.\n");
		/* Should this return -EBUSY instead? */
		return -ENOMEM;
	}

	ctx_entry = malloc(sizeof(*ctx_entry), DRM_MEM_CTXBITMAP, M_NOWAIT);
	if (!ctx_entry) {
		DRM_DEBUG("out of memory\n");
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&ctx_entry->head);
	ctx_entry->handle = ctx->handle;
	ctx_entry->tag = file_priv;

	DRM_LOCK(dev);
	list_add(&ctx_entry->head, &dev->ctxlist);
	++dev->ctx_count;
	DRM_UNLOCK(dev);

	return 0;
}