#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* screen; } ;
struct TYPE_7__ {int cell_x; int cell_y; } ;
struct TYPE_10__ {TYPE_2__ render_data; TYPE_1__ mouse_pos; } ;
typedef  TYPE_4__ Window ;
struct TYPE_9__ {int /*<<< orphan*/  mouse_tracking_protocol; } ;
struct TYPE_11__ {TYPE_3__ modes; } ;
typedef  TYPE_5__ Screen ;
typedef  int /*<<< orphan*/  MouseAction ;

/* Variables and functions */
 int encode_mouse_event_impl (unsigned int,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
encode_mouse_event(Window *w, int button, MouseAction action, int mods) {
    unsigned int x = w->mouse_pos.cell_x + 1, y = w->mouse_pos.cell_y + 1; // 1 based indexing
    Screen *screen = w->render_data.screen;
    return encode_mouse_event_impl(x, y, screen->modes.mouse_tracking_protocol, button, action, mods);

}