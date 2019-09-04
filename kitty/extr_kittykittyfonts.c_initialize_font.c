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
struct TYPE_3__ {scalar_t__ fonts; int /*<<< orphan*/  fonts_count; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ FontGroup ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 scalar_t__ PyErr_Occurred () ; 
 int /*<<< orphan*/  PyErr_Print () ; 
 int /*<<< orphan*/ * PyObject_CallFunction (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int PyObject_IsTrue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Py_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * desc_to_face (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  descriptor_for_idx ; 
 int /*<<< orphan*/  fatal (char*,char const*,...) ; 
 int init_font (scalar_t__,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static inline size_t
initialize_font(FontGroup *fg, unsigned int desc_idx, const char *ftype) {
    PyObject *d = PyObject_CallFunction(descriptor_for_idx, "I", desc_idx);
    if (d == NULL) { PyErr_Print(); fatal("Failed for %s font", ftype); }
    bool bold = PyObject_IsTrue(PyTuple_GET_ITEM(d, 1));
    bool italic = PyObject_IsTrue(PyTuple_GET_ITEM(d, 2));
    PyObject *face = desc_to_face(PyTuple_GET_ITEM(d, 0), (FONTS_DATA_HANDLE)fg);
    Py_CLEAR(d);
    if (face == NULL) { PyErr_Print(); fatal("Failed to convert descriptor to face for %s font", ftype); }
    size_t idx = fg->fonts_count++;
    bool ok = init_font(fg->fonts + idx, face, bold, italic, false);
    Py_CLEAR(face);
    if (!ok) {
        if (PyErr_Occurred()) { PyErr_Print(); }
        fatal("Failed to initialize %s font: %zu", ftype, idx);
    }
    return idx;
}