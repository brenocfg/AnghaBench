#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
struct TYPE_4__ {size_t num_os_windows; TYPE_1__* os_windows; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/  render_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RENDER_FRAME_READY ; 
 TYPE_2__ global_state ; 
 int /*<<< orphan*/  request_tick_callback () ; 

__attribute__((used)) static void
wayland_frame_request_callback(id_type os_window_id) {
    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        if (global_state.os_windows[i].id == os_window_id) {
            global_state.os_windows[i].render_state = RENDER_FRAME_READY;
            request_tick_callback();
            break;
        }
    }
}