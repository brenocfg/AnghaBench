#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ id_type ;
struct TYPE_4__ {size_t num_windows; TYPE_1__* windows; } ;
struct TYPE_3__ {scalar_t__ id; int /*<<< orphan*/ * title; } ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  END_WITH_TAB ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_INCREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WITH_TAB (scalar_t__,scalar_t__) ; 
 TYPE_2__* tab ; 

__attribute__((used)) static inline void
update_window_title(id_type os_window_id, id_type tab_id, id_type window_id, PyObject *title) {
    WITH_TAB(os_window_id, tab_id);
    for (size_t i = 0; i < tab->num_windows; i++) {
        if (tab->windows[i].id == window_id) {
            Py_CLEAR(tab->windows[i].title);
            tab->windows[i].title = title;
            Py_INCREF(tab->windows[i].title);
            break;
        }
    }
    END_WITH_TAB;
}