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
struct TYPE_3__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  i3string_as_utf8 (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool window_name_changed(i3Window *window, char *old_name) {
    if ((old_name == NULL) && (window->name == NULL))
        return false;

    /* Either the old or the new one is NULL, but not both. */
    if ((old_name == NULL) ^ (window->name == NULL))
        return true;

    return (strcmp(old_name, i3string_as_utf8(window->name)) != 0);
}