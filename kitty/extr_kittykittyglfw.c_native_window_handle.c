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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/ * PyLong_FromLong (long) ; 
 int /*<<< orphan*/ * Py_None ; 
 scalar_t__ glfwGetX11Window (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline PyObject*
native_window_handle(GLFWwindow *w) {
#ifdef __APPLE__
    void *ans = glfwGetCocoaWindow(w);
    return PyLong_FromVoidPtr(ans);
#endif
    if (glfwGetX11Window) return PyLong_FromLong((long)glfwGetX11Window(w));
    return Py_None;
}