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
struct TYPE_2__ {int id; } ;
struct drm_display_mode {int /*<<< orphan*/  head; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 

void drm_mode_copy(struct drm_display_mode *dst, const struct drm_display_mode *src)
{
	int id = dst->base.id;

	*dst = *src;
	dst->base.id = id;
	INIT_LIST_HEAD(&dst->head);
}