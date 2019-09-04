#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  state; int /*<<< orphan*/  activeUnknownModifiers; } ;
struct TYPE_8__ {TYPE_1__ states; int /*<<< orphan*/  numLockIdx; int /*<<< orphan*/  capsLockIdx; int /*<<< orphan*/  superIdx; int /*<<< orphan*/  shiftIdx; int /*<<< orphan*/  altIdx; int /*<<< orphan*/  controlIdx; } ;
typedef  TYPE_2__ _GLFWXKBData ;
struct TYPE_9__ {int /*<<< orphan*/  modifiers; int /*<<< orphan*/  state; } ;
typedef  TYPE_3__ XKBStateGroup ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_MOD_ALT ; 
 int /*<<< orphan*/  GLFW_MOD_CAPS_LOCK ; 
 int /*<<< orphan*/  GLFW_MOD_CONTROL ; 
 int /*<<< orphan*/  GLFW_MOD_NUM_LOCK ; 
 int /*<<< orphan*/  GLFW_MOD_SHIFT ; 
 int /*<<< orphan*/  GLFW_MOD_SUPER ; 
 int /*<<< orphan*/  XKB_STATE_MODS_EFFECTIVE ; 
 int /*<<< orphan*/  active_unknown_modifiers (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ xkb_state_mod_index_is_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_modifiers(_GLFWXKBData *xkb, XKBStateGroup *group) {
#define S(attr, name) if (xkb_state_mod_index_is_active(group->state, xkb->attr##Idx, XKB_STATE_MODS_EFFECTIVE)) group->modifiers |= GLFW_MOD_##name
    S(control, CONTROL); S(alt, ALT); S(shift, SHIFT); S(super, SUPER); S(capsLock, CAPS_LOCK); S(numLock, NUM_LOCK);
#undef S
    xkb->states.activeUnknownModifiers = active_unknown_modifiers(xkb, xkb->states.state);

}