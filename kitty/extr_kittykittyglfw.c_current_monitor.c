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
struct TYPE_3__ {int width; int height; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  PyErr_SetString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PyExc_ValueError ; 
 int /*<<< orphan*/  glfwGetMonitorPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ ** glfwGetMonitors (int*) ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 

__attribute__((used)) static GLFWmonitor*
current_monitor(GLFWwindow *window) {
    // Find the monitor that has the maximum overlap with this window
    int nmonitors, i;
    int wx, wy, ww, wh;
    int mx, my, mw, mh;
    int overlap = 0, bestoverlap = 0;
    GLFWmonitor *bestmonitor = NULL;
    GLFWmonitor **monitors = NULL;
    const GLFWvidmode *mode;

    glfwGetWindowPos(window, &wx, &wy);
    glfwGetWindowSize(window, &ww, &wh);
    monitors = glfwGetMonitors(&nmonitors);
    if (monitors == NULL || nmonitors < 1) { PyErr_SetString(PyExc_ValueError, "No monitors connected"); return NULL; }

    for (i = 0; i < nmonitors; i++) {
        mode = glfwGetVideoMode(monitors[i]);
        glfwGetMonitorPos(monitors[i], &mx, &my);
        mw = mode->width;
        mh = mode->height;

        overlap =
            MAX(0, MIN(wx + ww, mx + mw) - MAX(wx, mx)) *
            MAX(0, MIN(wy + wh, my + mh) - MAX(wy, my));

        if (bestoverlap < overlap || bestmonitor == NULL) {
            bestoverlap = overlap;
            bestmonitor = monitors[i];
        }
    }

    return bestmonitor;
}