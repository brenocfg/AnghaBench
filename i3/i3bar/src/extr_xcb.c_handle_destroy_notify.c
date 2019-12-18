#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  window; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ xcb_destroy_notify_event_t ;
struct TYPE_10__ {int /*<<< orphan*/  class_instance; int /*<<< orphan*/  class_class; } ;
typedef  TYPE_2__ trayclient ;
struct TYPE_11__ {int /*<<< orphan*/  trayclients; } ;
typedef  TYPE_3__ i3_output ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  configure_trayclients () ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tailq ; 
 TYPE_2__* trayclient_and_output_from_window (int /*<<< orphan*/ ,TYPE_3__**) ; 

__attribute__((used)) static void handle_destroy_notify(xcb_destroy_notify_event_t *event) {
    DLOG("DestroyNotify for window = %08x, event = %08x\n", event->window, event->event);

    i3_output *output;
    trayclient *client = trayclient_and_output_from_window(event->window, &output);
    if (!client) {
        DLOG("WARNING: Could not find corresponding tray window.\n");
        return;
    }

    DLOG("Removing tray client with window ID %08x\n", event->window);
    TAILQ_REMOVE(output->trayclients, client, tailq);
    free(client->class_class);
    free(client->class_instance);
    FREE(client);

    /* Trigger an update, we now have more space for the statusline */
    configure_trayclients();
    draw_bars(false);
}