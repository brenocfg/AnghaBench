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
struct xkb_rule_names {int /*<<< orphan*/  member_0; } ;
struct TYPE_3__ {int /*<<< orphan*/  default_keymap; int /*<<< orphan*/  context; int /*<<< orphan*/  keymap; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  XKB_KEYMAP_COMPILE_NO_FLAGS ; 
 int /*<<< orphan*/  xkb_glfw_load_keymap (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  xkb_keymap_new_from_names (int /*<<< orphan*/ ,struct xkb_rule_names*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char*
load_keymaps(_GLFWXKBData *xkb, const char *map_str) {
    (void)(map_str);  // not needed on X11
    xkb_glfw_load_keymap(xkb->keymap, map_str);
    if (!xkb->keymap) return "Failed to compile XKB keymap";
    // The system default keymap, can be overridden by the XKB_DEFAULT_RULES
    // env var, see
    // https://xkbcommon.org/doc/current/structxkb__rule__names.html
    static struct xkb_rule_names default_rule_names = {0};
    xkb->default_keymap = xkb_keymap_new_from_names(xkb->context, &default_rule_names, XKB_KEYMAP_COMPILE_NO_FLAGS);
    if (!xkb->default_keymap) return "Failed to create default XKB keymap";
    return NULL;
}