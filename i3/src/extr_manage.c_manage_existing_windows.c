#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_window_t ;
typedef  int /*<<< orphan*/  xcb_query_tree_reply_t ;
typedef  int /*<<< orphan*/  xcb_get_window_attributes_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manage_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * smalloc (int) ; 
 int /*<<< orphan*/  xcb_get_window_attributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_query_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_query_tree_children (int /*<<< orphan*/ *) ; 
 int xcb_query_tree_children_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xcb_query_tree_reply (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void manage_existing_windows(xcb_window_t root) {
    xcb_query_tree_reply_t *reply;
    int i, len;
    xcb_window_t *children;
    xcb_get_window_attributes_cookie_t *cookies;

    /* Get the tree of windows whose parent is the root window (= all) */
    if ((reply = xcb_query_tree_reply(conn, xcb_query_tree(conn, root), 0)) == NULL)
        return;

    len = xcb_query_tree_children_length(reply);
    cookies = smalloc(len * sizeof(*cookies));

    /* Request the window attributes for every window */
    children = xcb_query_tree_children(reply);
    for (i = 0; i < len; ++i)
        cookies[i] = xcb_get_window_attributes(conn, children[i]);

    /* Call manage_window with the attributes for every window */
    for (i = 0; i < len; ++i)
        manage_window(children[i], cookies[i], true);

    free(reply);
    free(cookies);
}