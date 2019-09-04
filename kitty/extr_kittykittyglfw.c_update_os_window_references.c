#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num_os_windows; TYPE_1__* os_windows; } ;
struct TYPE_4__ {scalar_t__ handle; } ;
typedef  TYPE_1__ OSWindow ;

/* Variables and functions */
 int /*<<< orphan*/  glfwSetWindowUserPointer (scalar_t__,TYPE_1__*) ; 
 TYPE_2__ global_state ; 

void
update_os_window_references() {
    for (size_t i = 0; i < global_state.num_os_windows; i++) {
        OSWindow *w = global_state.os_windows + i;
        if (w->handle) glfwSetWindowUserPointer(w->handle, w);
    }
}