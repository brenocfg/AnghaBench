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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int xkb_mod_mask_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_keyboard {int dummy; } ;
struct TYPE_4__ {int controlMask; int altMask; int shiftMask; int superMask; int capsLockMask; int numLockMask; unsigned int modifiers; int /*<<< orphan*/  state; int /*<<< orphan*/  keymap; } ;
struct TYPE_5__ {TYPE_1__ xkb; int /*<<< orphan*/  serial; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;

/* Variables and functions */
 unsigned int GLFW_MOD_ALT ; 
 unsigned int GLFW_MOD_CAPS_LOCK ; 
 unsigned int GLFW_MOD_CONTROL ; 
 unsigned int GLFW_MOD_NUM_LOCK ; 
 unsigned int GLFW_MOD_SHIFT ; 
 unsigned int GLFW_MOD_SUPER ; 
 int XKB_STATE_LAYOUT_DEPRESSED ; 
 int XKB_STATE_LAYOUT_LATCHED ; 
 int XKB_STATE_MODS_DEPRESSED ; 
 int XKB_STATE_MODS_LATCHED ; 
 TYPE_3__ _glfw ; 
 int xkb_state_serialize_mods (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xkb_state_update_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboardHandleModifiers(void* data,
                                    struct wl_keyboard* keyboard,
                                    uint32_t serial,
                                    uint32_t modsDepressed,
                                    uint32_t modsLatched,
                                    uint32_t modsLocked,
                                    uint32_t group)
{
    xkb_mod_mask_t mask;
    unsigned int modifiers = 0;

    _glfw.wl.serial = serial;

    if (!_glfw.wl.xkb.keymap)
        return;

    xkb_state_update_mask(_glfw.wl.xkb.state,
                          modsDepressed,
                          modsLatched,
                          modsLocked,
                          0,
                          0,
                          group);

    mask = xkb_state_serialize_mods(_glfw.wl.xkb.state,
                                    XKB_STATE_MODS_DEPRESSED |
                                    XKB_STATE_LAYOUT_DEPRESSED |
                                    XKB_STATE_MODS_LATCHED |
                                    XKB_STATE_LAYOUT_LATCHED);
    if (mask & _glfw.wl.xkb.controlMask)
        modifiers |= GLFW_MOD_CONTROL;
    if (mask & _glfw.wl.xkb.altMask)
        modifiers |= GLFW_MOD_ALT;
    if (mask & _glfw.wl.xkb.shiftMask)
        modifiers |= GLFW_MOD_SHIFT;
    if (mask & _glfw.wl.xkb.superMask)
        modifiers |= GLFW_MOD_SUPER;
    if (mask & _glfw.wl.xkb.capsLockMask)
        modifiers |= GLFW_MOD_CAPS_LOCK;
    if (mask & _glfw.wl.xkb.numLockMask)
        modifiers |= GLFW_MOD_NUM_LOCK;
    _glfw.wl.xkb.modifiers = modifiers;
}