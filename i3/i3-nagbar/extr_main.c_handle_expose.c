#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_expose_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_5__ {int width; scalar_t__ height; } ;

/* Variables and functions */
 scalar_t__ BAR_BORDER ; 
 int BTN_BORDER ; 
 scalar_t__ BTN_GAP ; 
 int BTN_PADDING ; 
 scalar_t__ CLOSE_BTN_GAP ; 
 int MSG_PADDING ; 
 TYPE_1__ bar ; 
 int /*<<< orphan*/  btn_close ; 
 scalar_t__ button_draw (int /*<<< orphan*/ *,int) ; 
 int buttoncnt ; 
 int /*<<< orphan*/ * buttons ; 
 int /*<<< orphan*/  color_background ; 
 int /*<<< orphan*/  color_border_bottom ; 
 int /*<<< orphan*/  color_text ; 
 int /*<<< orphan*/  draw_util_clear_surface (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_util_rectangle (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  draw_util_text (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  prompt ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_expose(xcb_connection_t *conn, xcb_expose_event_t *event) {
    /* draw background */
    draw_util_clear_surface(&bar, color_background);
    /* draw message */
    draw_util_text(prompt, &bar, color_text, color_background,
                   MSG_PADDING, MSG_PADDING,
                   bar.width - 2 * MSG_PADDING);

    int position = bar.width - (MSG_PADDING - BTN_BORDER - BTN_PADDING);

    /* render close button */
    position -= button_draw(&btn_close, position);
    position -= CLOSE_BTN_GAP;

    /* render custom buttons */
    for (int i = 0; i < buttoncnt; i++) {
        position -= BTN_GAP;
        position -= button_draw(&buttons[i], position);
    }

    /* border line at the bottom */
    draw_util_rectangle(&bar, color_border_bottom, 0, bar.height - BAR_BORDER, bar.width, BAR_BORDER);

    xcb_flush(conn);
    return 1;
}