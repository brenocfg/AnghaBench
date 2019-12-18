#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char xcb_get_property_reply_t ;
struct TYPE_3__ {char* role; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (char*) ; 
 int /*<<< orphan*/  LOG (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  sasprintf (char**,char*,scalar_t__,char*) ; 
 scalar_t__ xcb_get_property_value (char*) ; 
 scalar_t__ xcb_get_property_value_length (char*) ; 

void window_update_role(i3Window *win, xcb_get_property_reply_t *prop) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("WM_WINDOW_ROLE not set.\n");
        FREE(prop);
        return;
    }

    char *new_role;
    sasprintf(&new_role, "%.*s", xcb_get_property_value_length(prop),
              (char *)xcb_get_property_value(prop));
    FREE(win->role);
    win->role = new_role;
    LOG("WM_WINDOW_ROLE changed to \"%s\"\n", win->role);

    free(prop);
}