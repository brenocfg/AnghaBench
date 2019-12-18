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
struct drm_plane {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int /*<<< orphan*/  dc_plane_disable (struct drm_plane*) ; 
 int /*<<< orphan*/  drm_plane_cleanup (struct drm_plane*) ; 
 int /*<<< orphan*/  free (struct drm_plane*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dc_plane_destroy(struct drm_plane *plane)
{

	dc_plane_disable(plane);
	drm_plane_cleanup(plane);
	free(plane, DRM_MEM_KMS);
}