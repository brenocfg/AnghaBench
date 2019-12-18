#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
struct TYPE_10__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_1__ xcb_screen_t ;
struct TYPE_11__ {scalar_t__ bytes_after; scalar_t__ type; int /*<<< orphan*/  atom; } ;
typedef  TYPE_2__ xcb_intern_atom_reply_t ;
typedef  int /*<<< orphan*/  xcb_intern_atom_cookie_t ;
typedef  TYPE_2__ xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;

/* Variables and functions */
 scalar_t__ XCB_ATOM_CARDINAL ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 scalar_t__ ceil (double) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,unsigned int,...) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* xcb_aux_get_screen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * xcb_connect (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ xcb_connection_has_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 
 TYPE_2__* xcb_get_property_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property_unchecked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ xcb_get_property_value (TYPE_2__*) ; 
 int /*<<< orphan*/  xcb_get_property_value_length (TYPE_2__*) ; 
 int /*<<< orphan*/  xcb_intern_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* xcb_intern_atom_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

char *root_atom_contents(const char *atomname, xcb_connection_t *provided_conn, int screen) {
    xcb_intern_atom_cookie_t atom_cookie;
    xcb_intern_atom_reply_t *atom_reply;
    char *content = NULL;
    size_t content_max_words = 256;
    xcb_connection_t *conn = provided_conn;

    if (provided_conn == NULL &&
        ((conn = xcb_connect(NULL, &screen)) == NULL ||
         xcb_connection_has_error(conn))) {
        return NULL;
    }

    atom_cookie = xcb_intern_atom(conn, 0, strlen(atomname), atomname);

    xcb_screen_t *root_screen = xcb_aux_get_screen(conn, screen);
    xcb_window_t root = root_screen->root;

    atom_reply = xcb_intern_atom_reply(conn, atom_cookie, NULL);
    if (atom_reply == NULL) {
        goto out_conn;
    }

    xcb_get_property_cookie_t prop_cookie;
    xcb_get_property_reply_t *prop_reply;
    prop_cookie = xcb_get_property_unchecked(conn, false, root, atom_reply->atom,
                                             XCB_GET_PROPERTY_TYPE_ANY, 0, content_max_words);
    prop_reply = xcb_get_property_reply(conn, prop_cookie, NULL);
    if (prop_reply == NULL) {
        goto out_atom;
    }
    if (xcb_get_property_value_length(prop_reply) > 0 && prop_reply->bytes_after > 0) {
        /* We received an incomplete value. Ask again but with a properly
         * adjusted size. */
        content_max_words += ceil(prop_reply->bytes_after / 4.0);
        /* Repeat the request, with adjusted size */
        free(prop_reply);
        prop_cookie = xcb_get_property_unchecked(conn, false, root, atom_reply->atom,
                                                 XCB_GET_PROPERTY_TYPE_ANY, 0, content_max_words);
        prop_reply = xcb_get_property_reply(conn, prop_cookie, NULL);
        if (prop_reply == NULL) {
            goto out_atom;
        }
    }
    if (xcb_get_property_value_length(prop_reply) == 0) {
        goto out;
    }
    if (prop_reply->type == XCB_ATOM_CARDINAL) {
        /* We treat a CARDINAL as a >= 32-bit unsigned int. The only CARDINAL
         * we query is I3_PID, which is 32-bit. */
        sasprintf(&content, "%u", *((unsigned int *)xcb_get_property_value(prop_reply)));
    } else {
        sasprintf(&content, "%.*s", xcb_get_property_value_length(prop_reply),
                  (char *)xcb_get_property_value(prop_reply));
    }

out:
    free(prop_reply);
out_atom:
    free(atom_reply);
out_conn:
    if (provided_conn == NULL)
        xcb_disconnect(conn);
    return content;
}