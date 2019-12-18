#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ event_x; scalar_t__ event_y; } ;
typedef  TYPE_1__ xcb_button_press_event_t ;
struct TYPE_5__ {scalar_t__ height; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOD_Mod1 ; 
 int /*<<< orphan*/  MOD_Mod4 ; 
 scalar_t__ STEP_GENERATE ; 
 scalar_t__ col_x (int) ; 
 scalar_t__ current_step ; 
 TYPE_3__ font ; 
 int /*<<< orphan*/  handle_expose () ; 
 int /*<<< orphan*/  modifier ; 
 scalar_t__ row_y (int) ; 

__attribute__((used)) static void handle_button_press(xcb_button_press_event_t *event) {
    if (current_step != STEP_GENERATE)
        return;

    if (event->event_x < col_x(5) || event->event_x > col_x(10))
        return;

    if (event->event_y >= row_y(4) && event->event_y <= (row_y(4) + font.height)) {
        modifier = MOD_Mod4;
        handle_expose();
    }

    if (event->event_y >= row_y(5) && event->event_y <= (row_y(5) + font.height)) {
        modifier = MOD_Mod1;
        handle_expose();
    }
}