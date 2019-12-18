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
typedef  scalar_t__ bar_display_mode_t ;
struct TYPE_2__ {scalar_t__ hide_on_modifier; scalar_t__ command; int /*<<< orphan*/  colors; int /*<<< orphan*/  fontname; int /*<<< orphan*/  bar_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,char*) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  I3_IPC_MESSAGE_TYPE_GET_OUTPUTS ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/  draw_bars (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  free_colors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3_send_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_colors (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_xcb_late (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_child () ; 
 int /*<<< orphan*/  parse_config_json (char*) ; 
 int /*<<< orphan*/  reconfig_windows (int) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char* sstrdup (scalar_t__) ; 
 int /*<<< orphan*/  start_child (scalar_t__) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void got_bar_config_update(char *event) {
    /* check whether this affect this bar instance by checking the bar_id */
    char *expected_id;
    sasprintf(&expected_id, "\"id\":\"%s\"", config.bar_id);
    char *found_id = strstr(event, expected_id);
    FREE(expected_id);
    if (found_id == NULL)
        return;

    /* reconfigure the bar based on the current outputs */
    i3_send_msg(I3_IPC_MESSAGE_TYPE_GET_OUTPUTS, NULL);

    free_colors(&(config.colors));

    /* update the configuration with the received settings */
    DLOG("Received bar config update \"%s\"\n", event);
    char *old_command = config.command ? sstrdup(config.command) : NULL;
    bar_display_mode_t old_mode = config.hide_on_modifier;
    parse_config_json(event);
    if (old_mode != config.hide_on_modifier) {
        reconfig_windows(true);
    }

    /* update fonts and colors */
    init_xcb_late(config.fontname);
    init_colors(&(config.colors));

    /* restart status command process */
    if (old_command && strcmp(old_command, config.command) != 0) {
        kill_child();
        start_child(config.command);
    }
    free(old_command);

    draw_bars(false);
}