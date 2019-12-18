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
struct fb_info {struct fb_info* fb_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MEM_KMS ; 
 int /*<<< orphan*/  free (struct fb_info*,int /*<<< orphan*/ ) ; 

void
framebuffer_release(struct fb_info *info)
{

	free(info->fb_priv, DRM_MEM_KMS);
	free(info, DRM_MEM_KMS);
}