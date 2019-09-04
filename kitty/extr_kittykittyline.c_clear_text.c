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
typedef  int /*<<< orphan*/  PyObject ;
typedef  int /*<<< orphan*/  Line ;

/* Variables and functions */
 int BLANK_CHAR ; 
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*,int*) ; 
 int /*<<< orphan*/  Py_RETURN_NONE ; 
 int /*<<< orphan*/  line_clear_text (int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 

__attribute__((used)) static PyObject*
clear_text(Line* self, PyObject *args) {
#define clear_text_doc "clear_text(at, num, ch=BLANK_CHAR) -> Clear characters in the specified range, preserving formatting."
    unsigned int at, num;
    int ch = BLANK_CHAR;
    if (!PyArg_ParseTuple(args, "II|C", &at, &num, &ch)) return NULL;
    line_clear_text(self, at, num, ch);
    Py_RETURN_NONE;
}