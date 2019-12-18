#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int error_code; int overall_width; } ;
typedef  TYPE_5__ xcb_query_text_extents_reply_t ;
typedef  int /*<<< orphan*/  xcb_query_text_extents_cookie_t ;
typedef  TYPE_5__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_char2b_t ;
struct TYPE_13__ {TYPE_2__* info; int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_3__ xcb; } ;
struct TYPE_16__ {TYPE_4__ specific; } ;
struct TYPE_11__ {size_t character_width; } ;
struct TYPE_12__ {TYPE_1__ max_bounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 TYPE_9__* savedFont ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xcb_query_text_extents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 TYPE_5__* xcb_query_text_extents_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__**) ; 

__attribute__((used)) static int xcb_query_text_width(const xcb_char2b_t *text, size_t text_len) {
    /* Make the user know we’re using the slow path, but only once. */
    static bool first_invocation = true;
    if (first_invocation) {
        fprintf(stderr, "Using slow code path for text extents\n");
        first_invocation = false;
    }

    /* Query the text width */
    xcb_generic_error_t *error;
    xcb_query_text_extents_cookie_t cookie = xcb_query_text_extents(conn,
                                                                    savedFont->specific.xcb.id, text_len, (xcb_char2b_t *)text);
    xcb_query_text_extents_reply_t *reply = xcb_query_text_extents_reply(conn,
                                                                         cookie, &error);
    if (reply == NULL) {
        /* We return a safe estimate because a rendering error is better than
         * a crash. Plus, the user will see the error in their log. */
        fprintf(stderr, "Could not get text extents (X error code %d)\n",
                error->error_code);
        free(error);
        return savedFont->specific.xcb.info->max_bounds.character_width * text_len;
    }

    int width = reply->overall_width;
    free(reply);
    return width;
}