#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* ran_assignments; int /*<<< orphan*/  name; struct TYPE_4__* class_instance; struct TYPE_4__* class_class; } ;
typedef  TYPE_1__ i3Window ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  i3string_free (int /*<<< orphan*/ ) ; 

void window_free(i3Window *win) {
    FREE(win->class_class);
    FREE(win->class_instance);
    i3string_free(win->name);
    FREE(win->ran_assignments);
    FREE(win);
}