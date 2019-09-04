#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_17__ ;

/* Type definitions */
struct TYPE_25__ {double right; double left; double bottom; double top; } ;
typedef  TYPE_5__ WindowGeometry ;
struct TYPE_23__ {double x; double y; } ;
struct TYPE_21__ {TYPE_7__* screen; } ;
struct TYPE_26__ {TYPE_3__ mouse_pos; TYPE_1__ render_data; TYPE_5__ geometry; } ;
typedef  TYPE_6__ Window ;
struct TYPE_28__ {TYPE_4__* fonts_data; } ;
struct TYPE_27__ {int columns; int lines; } ;
struct TYPE_24__ {double cell_width; double cell_height; } ;
struct TYPE_22__ {double mouse_x; double mouse_y; } ;
struct TYPE_20__ {TYPE_2__* callback_os_window; } ;
typedef  TYPE_7__ Screen ;
typedef  TYPE_8__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  MAX (double,double) ; 
 double MIN (int /*<<< orphan*/ ,double) ; 
 scalar_t__ clamp_to_window ; 
 TYPE_17__ global_state ; 
 double window_bottom (TYPE_6__*,TYPE_8__*) ; 
 double window_left (TYPE_6__*,TYPE_8__*) ; 
 double window_right (TYPE_6__*,TYPE_8__*) ; 
 double window_top (TYPE_6__*,TYPE_8__*) ; 

__attribute__((used)) static inline bool
cell_for_pos(Window *w, unsigned int *x, unsigned int *y, OSWindow *os_window) {
    WindowGeometry *g = &w->geometry;
    Screen *screen = w->render_data.screen;
    if (!screen) return false;
    unsigned int qx = 0, qy = 0;
    double mouse_x = global_state.callback_os_window->mouse_x;
    double mouse_y = global_state.callback_os_window->mouse_y;
    double left = window_left(w, os_window), top = window_top(w, os_window), right = window_right(w, os_window), bottom = window_bottom(w, os_window);
    if (clamp_to_window) {
        mouse_x = MIN(MAX(mouse_x, left), right);
        mouse_y = MIN(MAX(mouse_y, top), bottom);
    }
    w->mouse_pos.x = mouse_x - left; w->mouse_pos.y = mouse_y - top;
    if (mouse_x < left || mouse_y < top || mouse_x > right || mouse_y > bottom) return false;
    if (mouse_x >= g->right) qx = screen->columns - 1;
    else if (mouse_x >= g->left) qx = (unsigned int)((double)(mouse_x - g->left) / os_window->fonts_data->cell_width);
    if (mouse_y >= g->bottom) qy = screen->lines - 1;
    else if (mouse_y >= g->top) qy = (unsigned int)((double)(mouse_y - g->top) / os_window->fonts_data->cell_height);
    if (qx < screen->columns && qy < screen->lines) {
        *x = qx; *y = qy;
        return true;
    }
    return false;
}