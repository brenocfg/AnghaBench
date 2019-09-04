#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cell_y; int /*<<< orphan*/  cell_x; } ;
struct TYPE_5__ {int /*<<< orphan*/ * screen; } ;
struct TYPE_7__ {TYPE_2__ mouse_pos; TYPE_1__ render_data; } ;
typedef  TYPE_3__ Window ;
typedef  int /*<<< orphan*/  Screen ;

/* Variables and functions */
 int /*<<< orphan*/  detect_url (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  screen_open_url (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
open_url(Window *w) {
    Screen *screen = w->render_data.screen;
    detect_url(screen, w->mouse_pos.cell_x, w->mouse_pos.cell_y);
    screen_open_url(screen);
}