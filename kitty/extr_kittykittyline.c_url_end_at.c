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
 int /*<<< orphan*/  PyArg_ParseTuple (int /*<<< orphan*/ *,char*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLong (unsigned long) ; 
 scalar_t__ line_url_end_at (int /*<<< orphan*/ *,unsigned int,int,unsigned int) ; 

__attribute__((used)) static PyObject*
url_end_at(Line *self, PyObject *args) {
#define url_end_at_doc "url_end_at(x) -> Return the end cell number for a URL containing x or 0 if not found"
    unsigned int x, sentinel = 0;
    if (!PyArg_ParseTuple(args, "I|I", &x, &sentinel)) return NULL;
    return PyLong_FromUnsignedLong((unsigned long)line_url_end_at(self, x, true, sentinel));
}