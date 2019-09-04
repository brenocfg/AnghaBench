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
typedef  int /*<<< orphan*/  xkb_keycode_t ;
struct TYPE_3__ {int /*<<< orphan*/  keymap; } ;
typedef  TYPE_1__ _GLFWXKBData ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_keymap_key_repeats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

GLFWbool
glfw_xkb_should_repeat(_GLFWXKBData *xkb, xkb_keycode_t scancode) {
#ifdef _GLFW_WAYLAND
    scancode += 8;
#endif
    return xkb_keymap_key_repeats(xkb->keymap, scancode);
}