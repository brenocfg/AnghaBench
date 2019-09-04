#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t index_type ;
typedef  scalar_t__ char_type ;
struct TYPE_7__ {char* cc_idx; scalar_t__ ch; } ;
struct TYPE_6__ {TYPE_1__* gpu_cells; TYPE_4__* cpu_cells; } ;
struct TYPE_5__ {scalar_t__ attrs; } ;
typedef  char Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_2__ Line ;

/* Variables and functions */
 int /*<<< orphan*/  PyUnicode_4BYTE_KIND ; 
 int /*<<< orphan*/ * PyUnicode_FromKindAndData (int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ WIDTH_MASK ; 
 int arraysz (char*) ; 
 scalar_t__ cell_as_unicode (TYPE_4__*,int,char*,char) ; 

PyObject*
unicode_in_range(Line *self, index_type start, index_type limit, bool include_cc, char leading_char) {
    size_t n = 0;
    static Py_UCS4 buf[4096];
    if (leading_char) buf[n++] = leading_char;
    char_type previous_width = 0;
    for(index_type i = start; i < limit && n < arraysz(buf) - 2 - arraysz(self->cpu_cells->cc_idx); i++) {
        char_type ch = self->cpu_cells[i].ch;
        if (ch == 0) {
            if (previous_width == 2) { previous_width = 0; continue; };
        }
        n += cell_as_unicode(self->cpu_cells + i, include_cc, buf + n, ' ');
        previous_width = self->gpu_cells[i].attrs & WIDTH_MASK;
    }
    return PyUnicode_FromKindAndData(PyUnicode_4BYTE_KIND, buf, n);
}