#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int color_type ;
struct TYPE_3__ {int last_titlebar_color; scalar_t__ handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */

void
set_titlebar_color(OSWindow *w, color_type color) {
    if (w->handle && (!w->last_titlebar_color || (w->last_titlebar_color & 0xffffff) != (color & 0xffffff))) {
        w->last_titlebar_color = (1 << 24) | (color & 0xffffff);
#ifdef __APPLE__
        cocoa_set_titlebar_color(glfwGetCocoaWindow(w->handle), color);
#endif
    }
}