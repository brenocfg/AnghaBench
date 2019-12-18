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
struct xkb_rule_names {int /*<<< orphan*/ * options; int /*<<< orphan*/ * variant; int /*<<< orphan*/ * layout; int /*<<< orphan*/ * model; int /*<<< orphan*/ * rules; } ;
struct xkb_keymap {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  LOG (char*) ; 
 int /*<<< orphan*/  conn ; 
 int fill_rmlvo_from_root (struct xkb_rule_names*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * xkb_context ; 
 int /*<<< orphan*/ * xkb_context_new (int /*<<< orphan*/ ) ; 
 struct xkb_keymap* xkb_keymap ; 
 struct xkb_keymap* xkb_keymap_new_from_names (int /*<<< orphan*/ *,struct xkb_rule_names*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_keymap_unref (struct xkb_keymap*) ; 
 scalar_t__ xkb_supported ; 
 int xkb_x11_get_core_keyboard_device_id (int /*<<< orphan*/ ) ; 
 struct xkb_keymap* xkb_x11_keymap_new_from_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

bool load_keymap(void) {
    if (xkb_context == NULL) {
        if ((xkb_context = xkb_context_new(0)) == NULL) {
            ELOG("Could not create xkbcommon context\n");
            return false;
        }
    }

    struct xkb_keymap *new_keymap = NULL;
    int32_t device_id;
    if (xkb_supported && (device_id = xkb_x11_get_core_keyboard_device_id(conn)) > -1) {
        if ((new_keymap = xkb_x11_keymap_new_from_device(xkb_context, conn, device_id, 0)) == NULL) {
            ELOG("xkb_x11_keymap_new_from_device failed\n");
            return false;
        }
    } else {
        /* Likely there is no XKB support on this server, possibly because it
         * is a VNC server. */
        LOG("No XKB / core keyboard device? Assembling keymap from local RMLVO.\n");
        struct xkb_rule_names names = {
            .rules = NULL,
            .model = NULL,
            .layout = NULL,
            .variant = NULL,
            .options = NULL};
        if (fill_rmlvo_from_root(&names) == -1) {
            ELOG("Could not get _XKB_RULES_NAMES atom from root window, falling back to defaults.\n");
            /* Using NULL for the fields of xkb_rule_names. */
        }
        new_keymap = xkb_keymap_new_from_names(xkb_context, &names, 0);
        free((char *)names.rules);
        free((char *)names.model);
        free((char *)names.layout);
        free((char *)names.variant);
        free((char *)names.options);
        if (new_keymap == NULL) {
            ELOG("xkb_keymap_new_from_names failed\n");
            return false;
        }
    }
    xkb_keymap_unref(xkb_keymap);
    xkb_keymap = new_keymap;

    return true;
}