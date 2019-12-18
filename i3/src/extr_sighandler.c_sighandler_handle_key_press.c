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
typedef  char xcb_keysym_t ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ xcb_key_press_event_t ;
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  backtrace_done ; 
 int /*<<< orphan*/  i3_restart (int) ; 
 int /*<<< orphan*/  keysyms ; 
 int /*<<< orphan*/  sighandler_backtrace () ; 
 int /*<<< orphan*/  sighandler_destroy_dialogs () ; 
 int /*<<< orphan*/  sighandler_handle_expose () ; 
 char xcb_key_press_lookup_keysym (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_numlock_mask ; 

__attribute__((used)) static void sighandler_handle_key_press(xcb_key_press_event_t *event) {
    uint16_t state = event->state;

    /* Apparently, after activating numlock once, the numlock modifier
     * stays turned on (use xev(1) to verify). So, to resolve useful
     * keysyms, we remove the numlock flag from the event state */
    state &= ~xcb_numlock_mask;

    xcb_keysym_t sym = xcb_key_press_lookup_keysym(keysyms, event, state);

    if (sym == 'b') {
        DLOG("User issued core-dump command.\n");

        /* fork and exec/attach GDB to the parent to get a backtrace in the
         * tmpdir */
        backtrace_done = sighandler_backtrace();
        sighandler_handle_expose();
    } else if (sym == 'r') {
        sighandler_destroy_dialogs();
        i3_restart(false);
    } else if (sym == 'f') {
        sighandler_destroy_dialogs();
        i3_restart(true);
    }
}