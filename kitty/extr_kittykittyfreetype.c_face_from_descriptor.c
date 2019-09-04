#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* tp_alloc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  face; } ;
typedef  int /*<<< orphan*/  PyObject ;
typedef  TYPE_1__ Face ;
typedef  int /*<<< orphan*/  FONTS_DATA_HANDLE ;

/* Variables and functions */
 int FT_New_Face (int /*<<< orphan*/ ,char const*,long,int /*<<< orphan*/ *) ; 
 TYPE_2__ Face_Type ; 
 int /*<<< orphan*/ * PyDict_GetItemString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_KeyError ; 
 long PyLong_AsLong (int /*<<< orphan*/ *) ; 
 int PyObject_IsTrue (int /*<<< orphan*/ *) ; 
 char* PyUnicode_AsUTF8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Py_CLEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  init_ft_face (TYPE_1__*,int /*<<< orphan*/ *,int,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  library ; 
 int /*<<< orphan*/  set_freetype_error (char*,int) ; 
 scalar_t__ stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

PyObject*
face_from_descriptor(PyObject *descriptor, FONTS_DATA_HANDLE fg) {
#define D(key, conv, missing_ok) { \
    PyObject *t = PyDict_GetItemString(descriptor, #key); \
    if (t == NULL) { \
        if (!missing_ok) { PyErr_SetString(PyExc_KeyError, "font descriptor is missing the key: " #key); return NULL; } \
    } else key = conv(t); \
}
    const char *path = NULL;
    long index = 0;
    bool hinting = false;
    long hint_style = 0;
    D(path, PyUnicode_AsUTF8, false);
    D(index, PyLong_AsLong, true);
    D(hinting, PyObject_IsTrue, true);
    D(hint_style, PyLong_AsLong, true);
#undef D
    Face *self = (Face *)Face_Type.tp_alloc(&Face_Type, 0);
    if (self != NULL) {
        int error = FT_New_Face(library, path, index, &(self->face));
        if(error) { set_freetype_error("Failed to load face, with error:", error); Py_CLEAR(self); return NULL; }
        if (!init_ft_face(self, PyDict_GetItemString(descriptor, "path"), hinting, hint_style, fg)) { Py_CLEAR(self); return NULL; }
    }
    return (PyObject*)self;
}