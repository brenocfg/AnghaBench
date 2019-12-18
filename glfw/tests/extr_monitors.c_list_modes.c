#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {float width; int height; } ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 char* format_mode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  glfwGetMonitorContentScale (int /*<<< orphan*/ *,float*,float*) ; 
 char* glfwGetMonitorName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetMonitorPhysicalSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetMonitorPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetMonitorWorkarea (int /*<<< orphan*/ *,int*,int*,int*,int*) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 TYPE_1__* glfwGetVideoModes (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ memcmp (TYPE_1__ const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void list_modes(GLFWmonitor* monitor)
{
    int count, x, y, width_mm, height_mm, i;
    int workarea_x, workarea_y, workarea_width, workarea_height;
    float xscale, yscale;

    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);

    glfwGetMonitorPos(monitor, &x, &y);
    glfwGetMonitorPhysicalSize(monitor, &width_mm, &height_mm);
    glfwGetMonitorContentScale(monitor, &xscale, &yscale);
    glfwGetMonitorWorkarea(monitor, &workarea_x, &workarea_y, &workarea_width, &workarea_height);

    printf("Name: %s (%s)\n",
           glfwGetMonitorName(monitor),
           glfwGetPrimaryMonitor() == monitor ? "primary" : "secondary");
    printf("Current mode: %s\n", format_mode(mode));
    printf("Virtual position: %i, %i\n", x, y);
    printf("Content scale: %f x %f\n", xscale, yscale);

    printf("Physical size: %i x %i mm (%0.2f dpi at %i x %i)\n",
           width_mm, height_mm, mode->width * 25.4f / width_mm, mode->width, mode->height);
    printf("Monitor work area: %i x %i starting at %i, %i\n",
            workarea_width, workarea_height, workarea_x, workarea_y);

    printf("Modes:\n");

    for (i = 0;  i < count;  i++)
    {
        printf("%3u: %s", (unsigned int) i, format_mode(modes + i));

        if (memcmp(mode, modes + i, sizeof(GLFWvidmode)) == 0)
            printf(" (current mode)");

        putchar('\n');
    }
}