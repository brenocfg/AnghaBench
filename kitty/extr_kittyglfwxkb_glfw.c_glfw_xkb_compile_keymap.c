#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t xkb_mod_index_t ;
struct TYPE_8__ {scalar_t__ activeUnknownModifiers; scalar_t__ modifiers; } ;
struct TYPE_9__ {int controlIdx; int controlMask; int altIdx; int altMask; int shiftIdx; int shiftMask; int superIdx; int superMask; int capsLockIdx; int capsLockMask; int numLockIdx; int numLockMask; size_t* unknownModifiers; TYPE_1__ states; int /*<<< orphan*/  keymap; } ;
typedef  TYPE_2__ _GLFWXKBData ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 size_t XKB_MOD_INVALID ; 
 int /*<<< orphan*/  XKB_MOD_NAME_ALT ; 
 int /*<<< orphan*/  XKB_MOD_NAME_CAPS ; 
 int /*<<< orphan*/  XKB_MOD_NAME_CTRL ; 
 int /*<<< orphan*/  XKB_MOD_NAME_LOGO ; 
 int /*<<< orphan*/  XKB_MOD_NAME_NUM ; 
 int /*<<< orphan*/  XKB_MOD_NAME_SHIFT ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  load_compose_tables (TYPE_2__*) ; 
 char* load_keymaps (TYPE_2__*,char const*) ; 
 char* load_states (TYPE_2__*) ; 
 int /*<<< orphan*/  release_keyboard_data (TYPE_2__*) ; 
 void* xkb_keymap_mod_get_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t xkb_keymap_num_mods (int /*<<< orphan*/ ) ; 

GLFWbool
glfw_xkb_compile_keymap(_GLFWXKBData *xkb, const char *map_str) {
    const char *err;
    release_keyboard_data(xkb);
    err = load_keymaps(xkb, map_str);
    if (err) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "%s", err);
        release_keyboard_data(xkb);
        return GLFW_FALSE;
    }
    err = load_states(xkb);
    if (err) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "%s", err);
        release_keyboard_data(xkb);
        return GLFW_FALSE;
    }
    load_compose_tables(xkb);
#define S(a, n) xkb->a##Idx = xkb_keymap_mod_get_index(xkb->keymap, n); xkb->a##Mask = 1 << xkb->a##Idx;
    S(control, XKB_MOD_NAME_CTRL);
    S(alt, XKB_MOD_NAME_ALT);
    S(shift, XKB_MOD_NAME_SHIFT);
    S(super, XKB_MOD_NAME_LOGO);
    S(capsLock, XKB_MOD_NAME_CAPS);
    S(numLock, XKB_MOD_NAME_NUM);
#undef S
    size_t capacity = sizeof(xkb->unknownModifiers)/sizeof(xkb->unknownModifiers[0]), j = 0;
    for (xkb_mod_index_t i = 0; i < capacity; i++) xkb->unknownModifiers[i] = XKB_MOD_INVALID;
    for (xkb_mod_index_t i = 0; i < xkb_keymap_num_mods(xkb->keymap) && j < capacity - 1; i++) {
        if (i != xkb->controlIdx && i != xkb->altIdx && i != xkb->shiftIdx && i != xkb->superIdx && i != xkb->capsLockIdx && i != xkb->numLockIdx) xkb->unknownModifiers[j++] = i;
    }
    xkb->states.modifiers = 0;
    xkb->states.activeUnknownModifiers = 0;
    return GLFW_TRUE;
}