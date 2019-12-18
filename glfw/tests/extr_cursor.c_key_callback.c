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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  refreshRate; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_CURSOR ; 
 int /*<<< orphan*/  GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_CURSOR_HIDDEN ; 
 int /*<<< orphan*/  GLFW_CURSOR_NORMAL ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
#define  GLFW_KEY_0 148 
#define  GLFW_KEY_1 147 
#define  GLFW_KEY_2 146 
#define  GLFW_KEY_3 145 
#define  GLFW_KEY_4 144 
#define  GLFW_KEY_5 143 
#define  GLFW_KEY_6 142 
#define  GLFW_KEY_A 141 
#define  GLFW_KEY_D 140 
#define  GLFW_KEY_DOWN 139 
#define  GLFW_KEY_ENTER 138 
#define  GLFW_KEY_ESCAPE 137 
#define  GLFW_KEY_F11 136 
#define  GLFW_KEY_H 135 
#define  GLFW_KEY_N 134 
#define  GLFW_KEY_P 133 
#define  GLFW_KEY_R 132 
#define  GLFW_KEY_SPACE 131 
#define  GLFW_KEY_T 130 
#define  GLFW_KEY_UP 129 
#define  GLFW_KEY_W 128 
 int GLFW_MOD_ALT ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RAW_MOUSE_MOTION ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int animate_cursor ; 
 double cursor_x ; 
 double cursor_y ; 
 int /*<<< orphan*/  glfwGetCursorPos (int /*<<< orphan*/ *,double*,double*) ; 
 int /*<<< orphan*/  glfwGetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwRawMouseMotionSupported () ; 
 int /*<<< orphan*/  glfwSetCursor (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetCursorPos (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ ** standard_cursors ; 
 int swap_interval ; 
 int track_cursor ; 
 int /*<<< orphan*/ * tracking_cursor ; 
 int wait_events ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_A:
        {
            animate_cursor = !animate_cursor;
            if (!animate_cursor)
                glfwSetCursor(window, NULL);

            break;
        }

        case GLFW_KEY_ESCAPE:
        {
            if (glfwGetInputMode(window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
            {
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;
            }

            /* FALLTHROUGH */
        }

        case GLFW_KEY_N:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            glfwGetCursorPos(window, &cursor_x, &cursor_y);
            printf("(( cursor is normal ))\n");
            break;

        case GLFW_KEY_D:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            printf("(( cursor is disabled ))\n");
            break;

        case GLFW_KEY_H:
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
            printf("(( cursor is hidden ))\n");
            break;

        case GLFW_KEY_R:
            if (!glfwRawMouseMotionSupported())
                break;

            if (glfwGetInputMode(window, GLFW_RAW_MOUSE_MOTION))
            {
                glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
                printf("(( raw input is disabled ))\n");
            }
            else
            {
                glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
                printf("(( raw input is enabled ))\n");
            }
            break;

        case GLFW_KEY_SPACE:
            swap_interval = 1 - swap_interval;
            printf("(( swap interval: %i ))\n", swap_interval);
            glfwSwapInterval(swap_interval);
            break;

        case GLFW_KEY_W:
            wait_events = !wait_events;
            printf("(( %sing for events ))\n", wait_events ? "wait" : "poll");
            break;

        case GLFW_KEY_T:
            track_cursor = !track_cursor;
            if (track_cursor)
                glfwSetCursor(window, tracking_cursor);
            else
                glfwSetCursor(window, NULL);

            break;

        case GLFW_KEY_P:
        {
            double x, y;
            glfwGetCursorPos(window, &x, &y);

            printf("Query before set: %f %f (%+f %+f)\n",
                   x, y, x - cursor_x, y - cursor_y);
            cursor_x = x;
            cursor_y = y;

            glfwSetCursorPos(window, cursor_x, cursor_y);
            glfwGetCursorPos(window, &x, &y);

            printf("Query after set: %f %f (%+f %+f)\n",
                   x, y, x - cursor_x, y - cursor_y);
            cursor_x = x;
            cursor_y = y;
            break;
        }

        case GLFW_KEY_UP:
            glfwSetCursorPos(window, 0, 0);
            glfwGetCursorPos(window, &cursor_x, &cursor_y);
            break;

        case GLFW_KEY_DOWN:
        {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glfwSetCursorPos(window, width - 1, height - 1);
            glfwGetCursorPos(window, &cursor_x, &cursor_y);
            break;
        }

        case GLFW_KEY_0:
            glfwSetCursor(window, NULL);
            break;

        case GLFW_KEY_1:
            glfwSetCursor(window, standard_cursors[0]);
            break;

        case GLFW_KEY_2:
            glfwSetCursor(window, standard_cursors[1]);
            break;

        case GLFW_KEY_3:
            glfwSetCursor(window, standard_cursors[2]);
            break;

        case GLFW_KEY_4:
            glfwSetCursor(window, standard_cursors[3]);
            break;

        case GLFW_KEY_5:
            glfwSetCursor(window, standard_cursors[4]);
            break;

        case GLFW_KEY_6:
            glfwSetCursor(window, standard_cursors[5]);
            break;

        case GLFW_KEY_F11:
        case GLFW_KEY_ENTER:
        {
            static int x, y, width, height;

            if (mods != GLFW_MOD_ALT)
                return;

            if (glfwGetWindowMonitor(window))
                glfwSetWindowMonitor(window, NULL, x, y, width, height, 0);
            else
            {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                glfwGetWindowPos(window, &x, &y);
                glfwGetWindowSize(window, &width, &height);
                glfwSetWindowMonitor(window, monitor,
                                     0, 0, mode->width, mode->height,
                                     mode->refreshRate);
            }

            glfwGetCursorPos(window, &cursor_x, &cursor_y);
            break;
        }
    }
}