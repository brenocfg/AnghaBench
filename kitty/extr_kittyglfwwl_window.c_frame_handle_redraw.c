#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_callback {int dummy; } ;
struct TYPE_4__ {struct wl_callback* current_wl_callback; int /*<<< orphan*/  id; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_1__ frameCallbackData; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_callback_destroy (struct wl_callback*) ; 

__attribute__((used)) static void
frame_handle_redraw(void *data, struct wl_callback *callback, uint32_t time) {
    _GLFWwindow* window = (_GLFWwindow*) data;
    if (callback == window->wl.frameCallbackData.current_wl_callback) {
        window->wl.frameCallbackData.callback(window->wl.frameCallbackData.id);
        window->wl.frameCallbackData.current_wl_callback = NULL;
    }
    wl_callback_destroy(callback);
}