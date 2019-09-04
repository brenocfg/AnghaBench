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
struct TYPE_4__ {int /*<<< orphan*/ * default_state; int /*<<< orphan*/ * clean_state; int /*<<< orphan*/ * state; int /*<<< orphan*/ * composeState; } ;
struct TYPE_5__ {TYPE_1__ states; int /*<<< orphan*/ * default_keymap; int /*<<< orphan*/ * keymap; } ;
typedef  TYPE_2__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_compose_state_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_keymap_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_state_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
release_keyboard_data(_GLFWXKBData *xkb) {
#define US(group, state, unref) if (xkb->group.state) {  unref(xkb->group.state); xkb->group.state = NULL; }
#define UK(keymap) if(xkb->keymap) { xkb_keymap_unref(xkb->keymap); xkb->keymap = NULL; }
    US(states, composeState, xkb_compose_state_unref);
    UK(keymap);
    UK(default_keymap);
    US(states, state, xkb_state_unref);
    US(states, clean_state, xkb_state_unref);
    US(states, default_state, xkb_state_unref);
#undef US
#undef UK

}