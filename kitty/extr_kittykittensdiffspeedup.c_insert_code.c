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
typedef  int /*<<< orphan*/  Py_UCS4 ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyUnicode_DATA (int /*<<< orphan*/ *) ; 
 unsigned int PyUnicode_GET_LENGTH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_KIND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PyUnicode_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline bool
insert_code(PyObject *code, Py_UCS4 *buf, size_t bufsz, unsigned int *buf_pos) {
    unsigned int csz = PyUnicode_GET_LENGTH(code);
    if (*buf_pos + csz >= bufsz) return false;
    for (unsigned int s = 0; s < csz; s++) buf[(*buf_pos)++] = PyUnicode_READ(PyUnicode_KIND(code), PyUnicode_DATA(code), s);
    return true;
}