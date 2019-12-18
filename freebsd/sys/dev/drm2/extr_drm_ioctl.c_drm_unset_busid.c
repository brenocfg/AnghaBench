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
struct drm_master {scalar_t__ unique_size; scalar_t__ unique_len; int /*<<< orphan*/ * unique; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_DRIVER ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
drm_unset_busid(struct drm_device *dev,
		struct drm_master *master)
{

	free(master->unique, DRM_MEM_DRIVER);
	master->unique = NULL;
	master->unique_len = 0;
	master->unique_size = 0;
}