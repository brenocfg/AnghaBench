#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ xcb_keycode_t ;
typedef  int /*<<< orphan*/  xcb_key_symbols_t ;
struct TYPE_4__ {int keycodes_per_modifier; } ;
typedef  TYPE_1__ xcb_get_modifier_mapping_reply_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__* xcb_get_modifier_mapping_keycodes (TYPE_1__*) ; 
 scalar_t__* xcb_key_symbols_get_keycode (int /*<<< orphan*/ *,int) ; 

uint32_t get_mod_mask_for(uint32_t keysym,
                          xcb_key_symbols_t *symbols,
                          xcb_get_modifier_mapping_reply_t *modmap_reply) {
    xcb_keycode_t *codes, *modmap;
    xcb_keycode_t mod_code;

    modmap = xcb_get_modifier_mapping_keycodes(modmap_reply);

    /* Get the list of keycodes for the given symbol */
    if (!(codes = xcb_key_symbols_get_keycode(symbols, keysym)))
        return 0;

    /* Loop through all modifiers (Mod1-Mod5, Shift, Control, Lock) */
    for (int mod = 0; mod < 8; mod++)
        for (int j = 0; j < modmap_reply->keycodes_per_modifier; j++) {
            /* Store the current keycode (for modifier 'mod') */
            mod_code = modmap[(mod * modmap_reply->keycodes_per_modifier) + j];
            /* Check if that keycode is in the list of previously resolved
             * keycodes for our symbol. If so, return the modifier mask. */
            for (xcb_keycode_t *code = codes; *code; code++) {
                if (*code != mod_code)
                    continue;

                free(codes);
                /* This corresponds to the XCB_MOD_MASK_* constants */
                return (1 << mod);
            }
        }

    return 0;
}