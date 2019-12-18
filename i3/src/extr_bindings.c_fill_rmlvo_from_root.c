#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ bytes_after; int /*<<< orphan*/  atom; } ;
typedef  TYPE_1__ xcb_intern_atom_reply_t ;
typedef  TYPE_1__ xcb_get_property_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_property_cookie_t ;
struct xkb_rule_names {int /*<<< orphan*/  options; int /*<<< orphan*/  variant; int /*<<< orphan*/  layout; int /*<<< orphan*/  model; int /*<<< orphan*/  rules; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*,int,int const,char const*) ; 
 int /*<<< orphan*/  XCB_GET_PROPERTY_TYPE_ANY ; 
 scalar_t__ ceil (double) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  sasprintf (char**,char*,int const,char const*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int strnlen (char const*,int) ; 
 TYPE_1__* xcb_get_property_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_property_unchecked (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ xcb_get_property_value (TYPE_1__*) ; 
 int xcb_get_property_value_length (TYPE_1__*) ; 
 int /*<<< orphan*/  xcb_intern_atom (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* xcb_intern_atom_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fill_rmlvo_from_root(struct xkb_rule_names *xkb_names) {
    xcb_intern_atom_reply_t *atom_reply;
    size_t content_max_words = 256;

    atom_reply = xcb_intern_atom_reply(
        conn, xcb_intern_atom(conn, 0, strlen("_XKB_RULES_NAMES"), "_XKB_RULES_NAMES"), NULL);
    if (atom_reply == NULL)
        return -1;

    xcb_get_property_cookie_t prop_cookie;
    xcb_get_property_reply_t *prop_reply;
    prop_cookie = xcb_get_property_unchecked(conn, false, root, atom_reply->atom,
                                             XCB_GET_PROPERTY_TYPE_ANY, 0, content_max_words);
    prop_reply = xcb_get_property_reply(conn, prop_cookie, NULL);
    if (prop_reply == NULL) {
        free(atom_reply);
        return -1;
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
            free(atom_reply);
            return -1;
        }
    }
    if (xcb_get_property_value_length(prop_reply) == 0) {
        free(atom_reply);
        free(prop_reply);
        return -1;
    }

    const char *walk = (const char *)xcb_get_property_value(prop_reply);
    int remaining = xcb_get_property_value_length(prop_reply);
    for (int i = 0; i < 5 && remaining > 0; i++) {
        const int len = strnlen(walk, remaining);
        switch (i) {
            case 0:
                sasprintf((char **)&(xkb_names->rules), "%.*s", len, walk);
                break;
            case 1:
                sasprintf((char **)&(xkb_names->model), "%.*s", len, walk);
                break;
            case 2:
                sasprintf((char **)&(xkb_names->layout), "%.*s", len, walk);
                break;
            case 3:
                sasprintf((char **)&(xkb_names->variant), "%.*s", len, walk);
                break;
            case 4:
                sasprintf((char **)&(xkb_names->options), "%.*s", len, walk);
                break;
        }
        DLOG("component %d of _XKB_RULES_NAMES is \"%.*s\"\n", i, len, walk);
        walk += (len + 1);
        remaining -= (len + 1);
    }

    free(atom_reply);
    free(prop_reply);
    return 0;
}