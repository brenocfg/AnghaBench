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
struct TYPE_4__ {scalar_t__ current_pos; scalar_t__ end_pos; int /*<<< orphan*/  start_code; int /*<<< orphan*/  end_code; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int PyList_Append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_4BYTE_KIND ; 
 int /*<<< orphan*/ * PyUnicode_FromKindAndData (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_code (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,unsigned int*) ; 

__attribute__((used)) static inline bool
add_line(Segment *bg_segment, Segment *fg_segment, Py_UCS4 *buf, size_t bufsz, unsigned int *buf_pos, PyObject *ans) {
    bool bg_is_active = bg_segment->current_pos == bg_segment->end_pos, fg_is_active = fg_segment->current_pos == fg_segment->end_pos;
    if (bg_is_active) { if(!insert_code(bg_segment->end_code, buf, bufsz, buf_pos)) return false; }
    if (fg_is_active) { if(!insert_code(fg_segment->end_code, buf, bufsz, buf_pos)) return false; }
    PyObject *wl = PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, buf, *buf_pos);
    if (!wl) return false;
    int ret = PyList_Append(ans, wl); Py_DECREF(wl); if (ret != 0) return false;
    *buf_pos = 0;
    if (bg_is_active) { if(!insert_code(bg_segment->start_code, buf, bufsz, buf_pos)) return false; }
    if (fg_is_active) { if(!insert_code(fg_segment->start_code, buf, bufsz, buf_pos)) return false; }
    return true;
}