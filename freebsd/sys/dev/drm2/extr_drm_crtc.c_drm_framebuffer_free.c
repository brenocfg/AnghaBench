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
struct drm_framebuffer {TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* destroy ) (struct drm_framebuffer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_framebuffer*) ; 

__attribute__((used)) static void drm_framebuffer_free(struct drm_framebuffer *fb)
{
	fb->funcs->destroy(fb);
}