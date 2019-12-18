#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_2__ xcb_expose_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_8__ {TYPE_1__ rect; int /*<<< orphan*/  frame; int /*<<< orphan*/  frame_buffer; } ;
typedef  TYPE_3__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 TYPE_3__* con_by_frame_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  draw_util_copy_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_expose_event(xcb_expose_event_t *event) {
    Con *parent;

    DLOG("window = %08x\n", event->window);

    if ((parent = con_by_frame_id(event->window)) == NULL) {
        LOG("expose event for unknown window, ignoring\n");
        return;
    }

    /* Since we render to our surface on every change anyways, expose events
     * only tell us that the X server lost (parts of) the window contents. */
    draw_util_copy_surface(&(parent->frame_buffer), &(parent->frame),
                           0, 0, 0, 0, parent->rect.width, parent->rect.height);
    xcb_flush(conn);
}