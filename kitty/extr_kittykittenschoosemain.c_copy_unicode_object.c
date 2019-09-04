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
typedef  int /*<<< orphan*/  text_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 void* PyUnicode_DATA (int /*<<< orphan*/ *) ; 
 size_t PyUnicode_GetLength (int /*<<< orphan*/ *) ; 
 int PyUnicode_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_READ (int,void*,size_t) ; 
 int /*<<< orphan*/  PyUnicode_READY (int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t
copy_unicode_object(PyObject *src, text_t *dest, size_t dest_sz) {
    PyUnicode_READY(src);
    int kind = PyUnicode_KIND(src);
    void *data = PyUnicode_DATA(src);
    size_t len = PyUnicode_GetLength(src);
    for (size_t i = 0; i < len && i < dest_sz; i++) {
        dest[i] = PyUnicode_READ(kind, data, i);
    }
    return len;
}