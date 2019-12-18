#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int major_version; int minor_version; int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ xcb_randr_query_version_reply_t ;
struct TYPE_9__ {int first_event; int /*<<< orphan*/  present; } ;
typedef  TYPE_2__ xcb_query_extension_reply_t ;
typedef  TYPE_1__ xcb_generic_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  ELOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCB_RANDR_MAJOR_VERSION ; 
 int /*<<< orphan*/  XCB_RANDR_MINOR_VERSION ; 
 int XCB_RANDR_NOTIFY_MASK_CRTC_CHANGE ; 
 int XCB_RANDR_NOTIFY_MASK_OUTPUT_CHANGE ; 
 int XCB_RANDR_NOTIFY_MASK_OUTPUT_PROPERTY ; 
 int XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  create_root_output (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fallback_to_root_output () ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int has_randr_1_5 ; 
 int /*<<< orphan*/  outputs ; 
 int /*<<< orphan*/  randr_query_outputs () ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  root_output ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ ) ; 
 TYPE_2__* xcb_get_extension_data (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_randr_id ; 
 int /*<<< orphan*/  xcb_randr_query_version (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_randr_query_version_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  xcb_randr_select_input (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void randr_init(int *event_base, const bool disable_randr15) {
    const xcb_query_extension_reply_t *extreply;

    root_output = create_root_output(conn);
    TAILQ_INSERT_TAIL(&outputs, root_output, outputs);

    extreply = xcb_get_extension_data(conn, &xcb_randr_id);
    if (!extreply->present) {
        DLOG("RandR is not present, activating root output.\n");
        fallback_to_root_output();
        return;
    }

    xcb_generic_error_t *err;
    xcb_randr_query_version_reply_t *randr_version =
        xcb_randr_query_version_reply(
            conn, xcb_randr_query_version(conn, XCB_RANDR_MAJOR_VERSION, XCB_RANDR_MINOR_VERSION), &err);
    if (err != NULL) {
        ELOG("Could not query RandR version: X11 error code %d\n", err->error_code);
        free(err);
        fallback_to_root_output();
        return;
    }

    has_randr_1_5 = (randr_version->major_version >= 1) &&
                    (randr_version->minor_version >= 5) &&
                    !disable_randr15;

    free(randr_version);

    randr_query_outputs();

    if (event_base != NULL)
        *event_base = extreply->first_event;

    xcb_randr_select_input(conn, root,
                           XCB_RANDR_NOTIFY_MASK_SCREEN_CHANGE |
                               XCB_RANDR_NOTIFY_MASK_OUTPUT_CHANGE |
                               XCB_RANDR_NOTIFY_MASK_CRTC_CHANGE |
                               XCB_RANDR_NOTIFY_MASK_OUTPUT_PROPERTY);

    xcb_flush(conn);
}