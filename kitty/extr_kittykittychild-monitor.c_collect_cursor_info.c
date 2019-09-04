#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_9__* screen; } ;
struct TYPE_16__ {TYPE_4__ render_data; } ;
typedef  TYPE_3__ Window ;
struct TYPE_22__ {TYPE_8__* color_profile; scalar_t__ scrolled_by; TYPE_7__* cursor; } ;
struct TYPE_15__ {int /*<<< orphan*/  cursor_color; } ;
struct TYPE_14__ {int /*<<< orphan*/  cursor_color; } ;
struct TYPE_21__ {TYPE_2__ configured; TYPE_1__ overridden; } ;
struct TYPE_20__ {int shape; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_19__ {int is_visible; int shape; scalar_t__ is_focused; int /*<<< orphan*/  color; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_18__ {double cursor_blink_zero_time; scalar_t__ is_focused; } ;
typedef  TYPE_4__ ScreenRenderData ;
typedef  TYPE_5__ OSWindow ;
typedef  TYPE_6__ CursorRenderInfo ;
typedef  TYPE_7__ Cursor ;
typedef  TYPE_8__ ColorProfile ;

/* Variables and functions */
 int OPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  colorprofile_to_color (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cursor_blink_interval ; 
 int /*<<< orphan*/  cursor_shape ; 
 int /*<<< orphan*/  cursor_stop_blinking_after ; 
 int /*<<< orphan*/  screen_is_cursor_visible (TYPE_9__*) ; 
 int /*<<< orphan*/  set_maximum_wait (double) ; 

__attribute__((used)) static inline void
collect_cursor_info(CursorRenderInfo *ans, Window *w, double now, OSWindow *os_window) {
    ScreenRenderData *rd = &w->render_data;
    Cursor *cursor = rd->screen->cursor;
    ans->x = cursor->x; ans->y = cursor->y;
    ans->is_visible = false;
    if (rd->screen->scrolled_by || !screen_is_cursor_visible(rd->screen)) return;
    double time_since_start_blink = now - os_window->cursor_blink_zero_time;
    bool cursor_blinking = OPT(cursor_blink_interval) > 0 && os_window->is_focused && (OPT(cursor_stop_blinking_after) == 0 || time_since_start_blink <= OPT(cursor_stop_blinking_after));
    bool do_draw_cursor = true;
    if (cursor_blinking) {
        int t = (int)(time_since_start_blink * 1000);
        int d = (int)(OPT(cursor_blink_interval) * 1000);
        int n = t / d;
        do_draw_cursor = n % 2 == 0 ? true : false;
        double bucket = (n + 1) * d;
        double delay = (bucket / 1000.0) - time_since_start_blink;
        set_maximum_wait(delay);
    }
    if (!do_draw_cursor) { ans->is_visible = false; return; }
    ans->is_visible = true;
    ColorProfile *cp = rd->screen->color_profile;
    ans->shape = cursor->shape ? cursor->shape : OPT(cursor_shape);
    ans->color = colorprofile_to_color(cp, cp->overridden.cursor_color, cp->configured.cursor_color);
    ans->is_focused = os_window->is_focused;
}