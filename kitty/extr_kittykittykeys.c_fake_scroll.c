#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Window ;

/* Variables and functions */
 int GLFW_KEY_DOWN ; 
 int GLFW_KEY_UP ; 
 int /*<<< orphan*/  GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 int /*<<< orphan*/ * active_window () ; 
 int /*<<< orphan*/  send_key_to_child (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fake_scroll(int amount, bool upwards) {
    Window *w = active_window();
    if (!w) return;
    int key = upwards ? GLFW_KEY_UP : GLFW_KEY_DOWN;
    while (amount-- > 0) {
        send_key_to_child(w, key, 0, GLFW_PRESS);
        send_key_to_child(w, key, 0, GLFW_RELEASE);
    }
}