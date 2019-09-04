#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ screen; } ;
struct TYPE_5__ {TYPE_1__ render_data; } ;
typedef  TYPE_2__ Window ;

/* Variables and functions */
 int /*<<< orphan*/  BEAM ; 
 int /*<<< orphan*/  mouse_cursor_shape ; 
 int /*<<< orphan*/  screen_mark_url (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_mouse_cursor (int /*<<< orphan*/ ) ; 
 TYPE_2__* window_for_event (unsigned int*,int*) ; 

void
focus_in_event() {
    // Ensure that no URL is highlighted and the mouse cursor is in default shape
    bool in_tab_bar;
    unsigned int window_idx = 0;
    mouse_cursor_shape = BEAM;
    set_mouse_cursor(BEAM);
    Window *w = window_for_event(&window_idx, &in_tab_bar);
    if (w && w->render_data.screen) screen_mark_url(w->render_data.screen, 0, 0, 0, 0);
}