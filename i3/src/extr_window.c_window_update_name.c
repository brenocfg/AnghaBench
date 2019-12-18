#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char xcb_get_property_reply_t ;
struct TYPE_6__ {int name_x_changed; int uses_net_wm_name; int /*<<< orphan*/ * name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ i3Window ;
typedef  int /*<<< orphan*/  i3String ;
struct TYPE_7__ {int /*<<< orphan*/ * title_format; } ;
typedef  TYPE_2__ Con ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  I3STRING_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* con_by_window_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * con_parse_title_format (TYPE_2__*) ; 
 int /*<<< orphan*/  ewmh_update_visible_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * i3string_from_utf8 (char*) ; 
 char* sstrndup (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  xcb_get_property_value (char*) ; 
 int xcb_get_property_value_length (char*) ; 

void window_update_name(i3Window *win, xcb_get_property_reply_t *prop) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("_NET_WM_NAME not specified, not changing\n");
        FREE(prop);
        return;
    }

    i3string_free(win->name);

    /* Truncate the name at the first zero byte. See #3515. */
    const int len = xcb_get_property_value_length(prop);
    char *name = sstrndup(xcb_get_property_value(prop), len);
    win->name = i3string_from_utf8(name);
    free(name);

    Con *con = con_by_window_id(win->id);
    if (con != NULL && con->title_format != NULL) {
        i3String *name = con_parse_title_format(con);
        ewmh_update_visible_name(win->id, i3string_as_utf8(name));
        I3STRING_FREE(name);
    }
    win->name_x_changed = true;
    LOG("_NET_WM_NAME changed to \"%s\"\n", i3string_as_utf8(win->name));

    win->uses_net_wm_name = true;

    free(prop);
}