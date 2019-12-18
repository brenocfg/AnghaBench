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
typedef  int /*<<< orphan*/  xcb_get_property_reply_t ;
struct TYPE_3__ {int /*<<< orphan*/ * class_class; int /*<<< orphan*/ * class_instance; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  DLOG (char*) ; 
 int /*<<< orphan*/  FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 void* sstrndup (char*,size_t const) ; 
 int strnlen (char*,size_t const) ; 
 char* xcb_get_property_value (int /*<<< orphan*/ *) ; 
 size_t xcb_get_property_value_length (int /*<<< orphan*/ *) ; 

void window_update_class(i3Window *win, xcb_get_property_reply_t *prop) {
    if (prop == NULL || xcb_get_property_value_length(prop) == 0) {
        DLOG("WM_CLASS not set.\n");
        FREE(prop);
        return;
    }

    /* We cannot use asprintf here since this property contains two
     * null-terminated strings (for compatibility reasons). Instead, we
     * use strdup() on both strings */
    const size_t prop_length = xcb_get_property_value_length(prop);
    char *new_class = xcb_get_property_value(prop);
    const size_t class_class_index = strnlen(new_class, prop_length) + 1;

    FREE(win->class_instance);
    FREE(win->class_class);

    win->class_instance = sstrndup(new_class, prop_length);
    if (class_class_index < prop_length)
        win->class_class = sstrndup(new_class + class_class_index, prop_length - class_class_index);
    else
        win->class_class = NULL;
    LOG("WM_CLASS changed to %s (instance), %s (class)\n",
        win->class_instance, win->class_class);

    free(prop);
}