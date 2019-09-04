#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ id; } ;
typedef  TYPE_3__ Window ;
struct TYPE_16__ {unsigned int num_windows; TYPE_1__* windows; } ;
typedef  TYPE_4__ Tab ;
struct TYPE_14__ {int active_tab; scalar_t__* mouse_button_pressed; TYPE_4__* tabs; } ;
struct TYPE_13__ {scalar_t__ id; } ;
struct TYPE_12__ {TYPE_2__* callback_os_window; scalar_t__ active_drag_in_window; } ;
typedef  scalar_t__ MouseShape ;

/* Variables and functions */
 int GLFW_MOUSE_BUTTON_LEFT ; 
 int GLFW_RELEASE ; 
 scalar_t__ HAND ; 
 int clamp_to_window ; 
 TYPE_3__* closest_window_for_event (unsigned int*) ; 
 int currently_pressed_button () ; 
 TYPE_10__ global_state ; 
 int /*<<< orphan*/  handle_event (TYPE_3__*,int,int,unsigned int) ; 
 int /*<<< orphan*/  handle_move_event (TYPE_3__*,int,int,unsigned int) ; 
 int /*<<< orphan*/  handle_tab_bar_mouse (int,int) ; 
 scalar_t__ mouse_cursor_shape ; 
 int /*<<< orphan*/  set_mouse_cursor (scalar_t__) ; 
 int /*<<< orphan*/  update_drag (int,TYPE_3__*,int,int) ; 
 TYPE_3__* window_for_event (unsigned int*,int*) ; 
 TYPE_3__* window_for_id (scalar_t__) ; 

void
mouse_event(int button, int modifiers, int action) {
    MouseShape old_cursor = mouse_cursor_shape;
    bool in_tab_bar;
    unsigned int window_idx = 0;
    Window *w = NULL;
    if (global_state.active_drag_in_window) {
        if (button == -1) {  // drag move
            w = window_for_id(global_state.active_drag_in_window);
            if (w) {
                button = currently_pressed_button();
                if (button == GLFW_MOUSE_BUTTON_LEFT) {
                    clamp_to_window = true;
                    Tab *t = global_state.callback_os_window->tabs + global_state.callback_os_window->active_tab;
                    for (window_idx = 0; window_idx < t->num_windows && t->windows[window_idx].id != w->id; window_idx++);
                    handle_move_event(w, button, modifiers, window_idx);
                    clamp_to_window = false;
                    return;
                }
            }
        }
        else if (action == GLFW_RELEASE && button == GLFW_MOUSE_BUTTON_LEFT) {
            w = window_for_id(global_state.active_drag_in_window);
            if (w) {
                update_drag(true, w, true, modifiers);
            }
        }
    }
    w = window_for_event(&window_idx, &in_tab_bar);
    if (in_tab_bar) {
        mouse_cursor_shape = HAND;
        handle_tab_bar_mouse(button, modifiers);
    } else if(w) {
        handle_event(w, button, modifiers, window_idx);
    } else if (button == GLFW_MOUSE_BUTTON_LEFT && global_state.callback_os_window->mouse_button_pressed[button]) {
        // initial click, clamp it to the closest window
        w = closest_window_for_event(&window_idx);
        if (w) {
            clamp_to_window = true;
            handle_event(w, button, modifiers, window_idx);
            clamp_to_window = false;
        }
    }
    if (mouse_cursor_shape != old_cursor) {
        set_mouse_cursor(mouse_cursor_shape);
    }
}