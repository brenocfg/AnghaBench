#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  command; int /*<<< orphan*/  colors; int /*<<< orphan*/  fontname; int /*<<< orphan*/  disable_ws; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char*) ; 
 int /*<<< orphan*/  I3_IPC_MESSAGE_TYPE_GET_OUTPUTS ; 
 int /*<<< orphan*/  I3_IPC_MESSAGE_TYPE_GET_WORKSPACES ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  free_colors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3_send_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_colors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_xcb_late (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_config_json (char*) ; 
 int /*<<< orphan*/  start_child (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subscribe_events () ; 

__attribute__((used)) static void got_bar_config(char *reply) {
    DLOG("Received bar config \"%s\"\n", reply);
    /* We initiate the main function by requesting infos about the outputs and
     * workspaces. Everything else (creating the bars, showing the right workspace-
     * buttons and more) is taken care of by the event-drivenness of the code */
    i3_send_msg(I3_IPC_MESSAGE_TYPE_GET_OUTPUTS, NULL);

    free_colors(&(config.colors));
    parse_config_json(reply);

    /* Now we can actually use 'config', so let's subscribe to the appropriate
     * events and request the workspaces if necessary. */
    subscribe_events();
    if (!config.disable_ws)
        i3_send_msg(I3_IPC_MESSAGE_TYPE_GET_WORKSPACES, NULL);

    /* Initialize the rest of XCB */
    init_xcb_late(config.fontname);

    /* Resolve color strings to colorpixels and save them, then free the strings. */
    init_colors(&(config.colors));

    start_child(config.command);
}