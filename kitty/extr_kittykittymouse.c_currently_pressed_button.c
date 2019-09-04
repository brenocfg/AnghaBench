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
struct TYPE_4__ {TYPE_1__* callback_os_window; } ;
struct TYPE_3__ {scalar_t__* mouse_button_pressed; } ;

/* Variables and functions */
 int GLFW_MOUSE_BUTTON_5 ; 
 TYPE_2__ global_state ; 

__attribute__((used)) static inline int
currently_pressed_button() {
    for (int i = 0; i < GLFW_MOUSE_BUTTON_5; i++) {
        if (global_state.callback_os_window->mouse_button_pressed[i]) return i;
    }
    return -1;
}