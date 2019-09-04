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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xkb_mod_mask_t ;
typedef  int /*<<< orphan*/  xkb_layout_index_t ;
struct TYPE_6__ {int /*<<< orphan*/  clean_state; int /*<<< orphan*/  state; scalar_t__ modifiers; } ;
struct TYPE_5__ {TYPE_3__ states; int /*<<< orphan*/  keymap; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  update_modifiers (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  xkb_state_update_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
glfw_xkb_update_modifiers(_GLFWXKBData *xkb, xkb_mod_mask_t depressed, xkb_mod_mask_t latched, xkb_mod_mask_t locked, xkb_layout_index_t base_group, xkb_layout_index_t latched_group, xkb_layout_index_t locked_group) {
    if (!xkb->keymap) return;
    xkb->states.modifiers = 0;
    xkb_state_update_mask(xkb->states.state, depressed, latched, locked, base_group, latched_group, locked_group);
    // We have to update the groups in clean_state, as they change for
    // different keyboard layouts, see https://github.com/kovidgoyal/kitty/issues/488
    xkb_state_update_mask(xkb->states.clean_state, 0, 0, 0, base_group, latched_group, locked_group);
    update_modifiers(xkb, &xkb->states);
}