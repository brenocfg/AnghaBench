#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int left; unsigned int top; } ;
struct TYPE_17__ {TYPE_1__ geometry; } ;
typedef  TYPE_5__ Window ;
struct TYPE_19__ {TYPE_4__* fonts_data; } ;
struct TYPE_18__ {TYPE_2__* cursor; } ;
struct TYPE_16__ {unsigned int cell_width; unsigned int cell_height; } ;
struct TYPE_15__ {int /*<<< orphan*/  handle; } ;
struct TYPE_14__ {unsigned int x; unsigned int y; } ;
struct TYPE_12__ {TYPE_3__* callback_os_window; } ;
typedef  TYPE_6__ Screen ;
typedef  TYPE_7__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwUpdateIMEState (int /*<<< orphan*/ ,int,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 TYPE_11__ global_state ; 

__attribute__((used)) static inline void
update_ime_position(OSWindow *os_window, Window* w, Screen *screen) {
    unsigned int cell_width = os_window->fonts_data->cell_width, cell_height = os_window->fonts_data->cell_height;
    unsigned int left = w->geometry.left, top = w->geometry.top;
    left += screen->cursor->x * cell_width;
    top += screen->cursor->y * cell_height;
    glfwUpdateIMEState(global_state.callback_os_window->handle, 2, left, top, cell_width, cell_height);
}