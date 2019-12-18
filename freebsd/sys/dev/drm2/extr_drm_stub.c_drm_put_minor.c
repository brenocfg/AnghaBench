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
struct drm_minor {int /*<<< orphan*/  device; int /*<<< orphan*/  buf_sigio; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_MEM_MINOR ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct drm_minor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  funsetown (int /*<<< orphan*/ *) ; 

int drm_put_minor(struct drm_minor **minor_p)
{
	struct drm_minor *minor = *minor_p;

	DRM_DEBUG("release secondary minor %d\n", minor->index);

	funsetown(&minor->buf_sigio);

	destroy_dev(minor->device);

	free(minor, DRM_MEM_MINOR);
	*minor_p = NULL;
	return 0;
}