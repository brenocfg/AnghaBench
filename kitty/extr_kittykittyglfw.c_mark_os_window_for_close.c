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
struct TYPE_5__ {int has_pending_closes; } ;
struct TYPE_4__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ ,int) ; 
 TYPE_3__ global_state ; 

void
mark_os_window_for_close(OSWindow* w, bool yes) {
    global_state.has_pending_closes = true;
    glfwSetWindowShouldClose(w->handle, yes);
}