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
 int /*<<< orphan*/  PyLong_AsUnsignedLong (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PyLong_FromUnsignedLong (unsigned long) ; 
 scalar_t__ line_url_start_at (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PyObject*
url_start_at(Line *self, PyObject *x) {
#define url_start_at_doc "url_start_at(x) -> Return the start cell number for a URL containing x or self->xnum if not found"
    return PyLong_FromUnsignedLong((unsigned long)line_url_start_at(self, PyLong_AsUnsignedLong(x)));
}