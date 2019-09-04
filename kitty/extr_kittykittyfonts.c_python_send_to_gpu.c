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
typedef  int /*<<< orphan*/  pixel ;
struct TYPE_3__ {int cell_width; int cell_height; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__* FONTS_DATA_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  PyBytes_FromStringAndSize (char const*,int) ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyObject_CallFunction (scalar_t__,char*,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Py_DECREF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  num_font_groups ; 
 scalar_t__ python_send_to_gpu_impl ; 

__attribute__((used)) static void
python_send_to_gpu(FONTS_DATA_HANDLE fg, unsigned int x, unsigned int y, unsigned int z, pixel* buf) {
    if (python_send_to_gpu_impl) {
        if (!num_font_groups) fatal("Cannot call send to gpu with no font groups");
        PyObject *ret = PyObject_CallFunction(python_send_to_gpu_impl, "IIIN", x, y, z, PyBytes_FromStringAndSize((const char*)buf, sizeof(pixel) * fg->cell_width * fg->cell_height));
        if (ret == NULL) PyErr_Print();
        else Py_DECREF(ret);
    }
}