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
struct wt_status {char** color_palette; int /*<<< orphan*/  use_color; } ;

/* Variables and functions */
 size_t WT_STATUS_HEADER ; 
 int WT_STATUS_ONBRANCH ; 
 scalar_t__ color_is_nil (char const*) ; 
 scalar_t__ want_color (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *color(int slot, struct wt_status *s)
{
	const char *c = "";
	if (want_color(s->use_color))
		c = s->color_palette[slot];
	if (slot == WT_STATUS_ONBRANCH && color_is_nil(c))
		c = s->color_palette[WT_STATUS_HEADER];
	return c;
}