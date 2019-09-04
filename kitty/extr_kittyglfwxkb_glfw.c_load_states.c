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
struct TYPE_4__ {void* default_state; void* clean_state; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__ states; int /*<<< orphan*/  default_keymap; int /*<<< orphan*/  keymap; } ;
typedef  TYPE_2__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_glfw_load_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* xkb_state_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
load_states(_GLFWXKBData *xkb) {
    xkb_glfw_load_state(xkb->keymap, xkb->states.state);
    xkb->states.clean_state = xkb_state_new(xkb->keymap);
    xkb->states.default_state = xkb_state_new(xkb->default_keymap);
    if (!xkb->states.state || !xkb->states.clean_state || !xkb->states.default_state) return "Failed to create XKB state";
    return NULL;
}