#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  current_pos; } ;
struct TYPE_4__ {scalar_t__ pos; scalar_t__ num; TYPE_3__ sg; } ;
typedef  TYPE_1__ SegmentPointer ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyList_GET_ITEM (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UINT_MAX ; 
 int /*<<< orphan*/  convert_segment (int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static inline bool
next_segment(SegmentPointer *s, PyObject *highlights) {
    if (s->pos < s->num) {
        if (!convert_segment(PyList_GET_ITEM(highlights, s->pos), &s->sg)) return false;
        s->pos++;
    } else s->sg.current_pos = UINT_MAX;
    return true;
}