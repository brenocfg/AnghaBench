#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  render_state; int /*<<< orphan*/  id; int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  RENDER_FRAME_REQUESTED ; 
 int /*<<< orphan*/  glfwRequestWaylandFrameEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wayland_frame_request_callback ; 

void
request_frame_render(OSWindow *w) {
    glfwRequestWaylandFrameEvent(w->handle, w->id, wayland_frame_request_callback);
    w->render_state = RENDER_FRAME_REQUESTED;
}