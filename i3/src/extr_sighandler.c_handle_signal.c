#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_key_press_event_t ;
struct TYPE_5__ {int response_type; } ;
typedef  TYPE_1__ xcb_generic_event_t ;
struct TYPE_6__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_2__ xcb_expose_event_t ;
struct sigaction {int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int) ; 
 int /*<<< orphan*/  SIG_DFL ; 
#define  XCB_EXPOSE 129 
#define  XCB_KEY_PRESS 128 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int raised_signal ; 
 int /*<<< orphan*/  sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler_create_dialogs () ; 
 int /*<<< orphan*/  sighandler_handle_expose () ; 
 int /*<<< orphan*/  sighandler_handle_key_press (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighandler_setup () ; 
 TYPE_1__* xcb_wait_for_event (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_signal(int sig, siginfo_t *info, void *data) {
    DLOG("i3 crashed. SIG: %d\n", sig);

    struct sigaction action;
    action.sa_handler = SIG_DFL;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    sigaction(sig, &action, NULL);
    raised_signal = sig;

    sighandler_setup();
    sighandler_create_dialogs();

    xcb_generic_event_t *event;
    /* Yay, more own eventhandlers… */
    while ((event = xcb_wait_for_event(conn))) {
        /* Strip off the highest bit (set if the event is generated) */
        int type = (event->response_type & 0x7F);
        switch (type) {
            case XCB_KEY_PRESS:
                sighandler_handle_key_press((xcb_key_press_event_t *)event);
                break;
            case XCB_EXPOSE:
                if (((xcb_expose_event_t *)event)->count == 0) {
                    sighandler_handle_expose();
                }

                break;
        }

        free(event);
    }
}