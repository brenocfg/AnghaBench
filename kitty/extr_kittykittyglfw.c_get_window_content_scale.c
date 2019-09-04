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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  glfwGetMonitorContentScale (int /*<<< orphan*/ *,float*,float*) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/  glfwGetWindowContentScale (int /*<<< orphan*/ *,float*,float*) ; 

__attribute__((used)) static inline void
get_window_content_scale(GLFWwindow *w, float *xscale, float *yscale, double *xdpi, double *ydpi) {
    if (w) glfwGetWindowContentScale(w, xscale, yscale);
    else {
        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        if (monitor) glfwGetMonitorContentScale(monitor, xscale, yscale);
    }
    // check for zero, negative, NaN or excessive values of xscale/yscale
    if (*xscale <= 0 || *xscale != *xscale || *xscale >= 24) *xscale = 1.0;
    if (*yscale <= 0 || *yscale != *yscale || *yscale >= 24) *yscale = 1.0;
#ifdef __APPLE__
    const double factor = 72.0;
#else
    const double factor = 96.0;
#endif
    *xdpi = *xscale * factor;
    *ydpi = *yscale * factor;
}