#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int xcb_keysym_t ;
typedef  scalar_t__ xcb_keycode_t ;
struct TYPE_6__ {int detail; int state; } ;
typedef  TYPE_1__ xcb_key_press_event_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
typedef  int uint16_t ;
struct TYPE_7__ {int keycodes_per_modifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_UTF8_STRING ; 
 int /*<<< orphan*/  A__NET_WM_NAME ; 
 scalar_t__ MOD_Mod1 ; 
 scalar_t__ MOD_Mod4 ; 
 scalar_t__ STEP_GENERATE ; 
 scalar_t__ STEP_WELCOME ; 
 int XCB_MOD_MASK_LOCK ; 
 scalar_t__ XCB_NONE ; 
 int /*<<< orphan*/  XCB_PROP_MODE_REPLACE ; 
 int XK_Down ; 
 int XK_Escape ; 
 int XK_KP_Enter ; 
 int XK_Return ; 
 int XK_Up ; 
 scalar_t__ current_step ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish () ; 
 int /*<<< orphan*/  handle_expose () ; 
 scalar_t__ modifier ; 
 TYPE_3__* modmap_reply ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  symbols ; 
 int /*<<< orphan*/  win ; 
 int /*<<< orphan*/  xcb_change_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 
 scalar_t__* xcb_get_modifier_mapping_keycodes (TYPE_3__*) ; 
 int xcb_key_press_lookup_keysym (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int xcb_numlock_mask ; 

__attribute__((used)) static int handle_key_press(void *ignored, xcb_connection_t *conn, xcb_key_press_event_t *event) {
    printf("Keypress %d, state raw = %d\n", event->detail, event->state);

    /* Remove the numlock bit, all other bits are modifiers we can bind to */
    uint16_t state_filtered = event->state & ~(xcb_numlock_mask | XCB_MOD_MASK_LOCK);
    /* Only use the lower 8 bits of the state (modifier masks) so that mouse
     * button masks are filtered out */
    state_filtered &= 0xFF;

    xcb_keysym_t sym = xcb_key_press_lookup_keysym(symbols, event, state_filtered);

    printf("sym = %c (%d)\n", sym, sym);

    if (sym == XK_Return || sym == XK_KP_Enter) {
        if (current_step == STEP_WELCOME) {
            current_step = STEP_GENERATE;
            /* Set window title */
            xcb_change_property(conn,
                                XCB_PROP_MODE_REPLACE,
                                win,
                                A__NET_WM_NAME,
                                A_UTF8_STRING,
                                8,
                                strlen("i3: generate config"),
                                "i3: generate config");
            xcb_flush(conn);
        } else
            finish();
    }

    /* Swap between modifiers when up or down is pressed. */
    if (sym == XK_Up || sym == XK_Down) {
        modifier = (modifier == MOD_Mod1) ? MOD_Mod4 : MOD_Mod1;
        handle_expose();
    }

    /* cancel any time */
    if (sym == XK_Escape)
        exit(0);

    /* Check if this is Mod1 or Mod4. The modmap contains Shift, Lock, Control,
     * Mod1, Mod2, Mod3, Mod4, Mod5 (in that order) */
    xcb_keycode_t *modmap = xcb_get_modifier_mapping_keycodes(modmap_reply);
    /* Mod1? */
    int mask = 3;
    for (int i = 0; i < modmap_reply->keycodes_per_modifier; i++) {
        xcb_keycode_t code = modmap[(mask * modmap_reply->keycodes_per_modifier) + i];
        if (code == XCB_NONE)
            continue;
        printf("Modifier keycode for Mod1: 0x%02x\n", code);
        if (code == event->detail) {
            modifier = MOD_Mod1;
            printf("This is Mod1!\n");
        }
    }

    /* Mod4? */
    mask = 6;
    for (int i = 0; i < modmap_reply->keycodes_per_modifier; i++) {
        xcb_keycode_t code = modmap[(mask * modmap_reply->keycodes_per_modifier) + i];
        if (code == XCB_NONE)
            continue;
        printf("Modifier keycode for Mod4: 0x%02x\n", code);
        if (code == event->detail) {
            modifier = MOD_Mod4;
            printf("This is Mod4!\n");
        }
    }

    handle_expose();
    return 1;
}