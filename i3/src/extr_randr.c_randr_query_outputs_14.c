#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_timestamp_t ;
typedef  int /*<<< orphan*/  xcb_randr_output_t ;
struct TYPE_9__ {int /*<<< orphan*/  config_timestamp; } ;
typedef  TYPE_1__ xcb_randr_get_screen_resources_current_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_screen_resources_current_cookie_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_output_primary_cookie_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_output_info_reply_t ;
typedef  int /*<<< orphan*/  xcb_randr_get_output_info_cookie_t ;
struct TYPE_10__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,...) ; 
 int /*<<< orphan*/  ELOG (char*) ; 
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,TYPE_1__*) ; 
 TYPE_5__* primary ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  xcb_randr_get_output_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/ * xcb_randr_get_output_info_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_output_primary (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__* xcb_randr_get_output_primary_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_get_screen_resources_current (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_randr_get_screen_resources_current_outputs (TYPE_1__*) ; 
 int xcb_randr_get_screen_resources_current_outputs_length (TYPE_1__*) ; 
 TYPE_1__* xcb_randr_get_screen_resources_current_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void randr_query_outputs_14(void) {
    DLOG("Querying outputs using RandR ≤ 1.4\n");

    /* Get screen resources (primary output, crtcs, outputs, modes) */
    xcb_randr_get_screen_resources_current_cookie_t rcookie;
    rcookie = xcb_randr_get_screen_resources_current(conn, root);
    xcb_randr_get_output_primary_cookie_t pcookie;
    pcookie = xcb_randr_get_output_primary(conn, root);

    if ((primary = xcb_randr_get_output_primary_reply(conn, pcookie, NULL)) == NULL)
        ELOG("Could not get RandR primary output\n");
    else
        DLOG("primary output is %08x\n", primary->output);

    xcb_randr_get_screen_resources_current_reply_t *res =
        xcb_randr_get_screen_resources_current_reply(conn, rcookie, NULL);
    if (res == NULL) {
        ELOG("Could not query screen resources.\n");
        return;
    }

    /* timestamp of the configuration so that we get consistent replies to all
     * requests (if the configuration changes between our different calls) */
    const xcb_timestamp_t cts = res->config_timestamp;

    const int len = xcb_randr_get_screen_resources_current_outputs_length(res);

    /* an output is VGA-1, LVDS-1, etc. (usually physical video outputs) */
    xcb_randr_output_t *randr_outputs = xcb_randr_get_screen_resources_current_outputs(res);

    /* Request information for each output */
    xcb_randr_get_output_info_cookie_t ocookie[len];
    for (int i = 0; i < len; i++)
        ocookie[i] = xcb_randr_get_output_info(conn, randr_outputs[i], cts);

    /* Loop through all outputs available for this X11 screen */
    for (int i = 0; i < len; i++) {
        xcb_randr_get_output_info_reply_t *output;

        if ((output = xcb_randr_get_output_info_reply(conn, ocookie[i], NULL)) == NULL)
            continue;

        handle_output(conn, randr_outputs[i], output, cts, res);
        free(output);
    }

    FREE(res);
}