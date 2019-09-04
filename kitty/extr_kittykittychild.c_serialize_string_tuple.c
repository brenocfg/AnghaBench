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
typedef  size_t Py_ssize_t ;
typedef  int /*<<< orphan*/  PyObject ;

/* Variables and functions */
 int /*<<< orphan*/  PyTuple_GET_ITEM (int /*<<< orphan*/ *,size_t) ; 
 size_t PyTuple_GET_SIZE (int /*<<< orphan*/ *) ; 
 char* PyUnicode_AsUTF8 (int /*<<< orphan*/ ) ; 
 void* calloc (size_t,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static inline char**
serialize_string_tuple(PyObject *src) {
    Py_ssize_t sz = PyTuple_GET_SIZE(src);

    char **ans = calloc(sz + 1, sizeof(char*));
    if (!ans) fatal("Out of memory");
    for (Py_ssize_t i = 0; i < sz; i++) {
        const char *pysrc = PyUnicode_AsUTF8(PyTuple_GET_ITEM(src, i));
        size_t len = strlen(pysrc);
        ans[i] = calloc(len + 1, sizeof(char));
        if (ans[i] == NULL) fatal("Out of memory");
        memcpy(ans[i], pysrc, len);
    }
    return ans;
}