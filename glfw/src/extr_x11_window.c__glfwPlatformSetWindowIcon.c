#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  handle; } ;
struct TYPE_10__ {TYPE_1__ x11; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_9__ {int /*<<< orphan*/  display; int /*<<< orphan*/  NET_WM_ICON; } ;
struct TYPE_12__ {TYPE_2__ x11; } ;
struct TYPE_11__ {int width; int height; int* pixels; } ;
typedef  TYPE_4__ GLFWimage ;

/* Variables and functions */
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XDeleteProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 TYPE_7__ _glfw ; 
 long* calloc (int,int) ; 
 int /*<<< orphan*/  free (long*) ; 

void _glfwPlatformSetWindowIcon(_GLFWwindow* window,
                                int count, const GLFWimage* images)
{
    if (count)
    {
        int i, j, longCount = 0;

        for (i = 0;  i < count;  i++)
            longCount += 2 + images[i].width * images[i].height;

        long* icon = calloc(longCount, sizeof(long));
        long* target = icon;

        for (i = 0;  i < count;  i++)
        {
            *target++ = images[i].width;
            *target++ = images[i].height;

            for (j = 0;  j < images[i].width * images[i].height;  j++)
            {
                *target++ = (images[i].pixels[j * 4 + 0] << 16) |
                            (images[i].pixels[j * 4 + 1] <<  8) |
                            (images[i].pixels[j * 4 + 2] <<  0) |
                            (images[i].pixels[j * 4 + 3] << 24);
            }
        }

        XChangeProperty(_glfw.x11.display, window->x11.handle,
                        _glfw.x11.NET_WM_ICON,
                        XA_CARDINAL, 32,
                        PropModeReplace,
                        (unsigned char*) icon,
                        longCount);

        free(icon);
    }
    else
    {
        XDeleteProperty(_glfw.x11.display, window->x11.handle,
                        _glfw.x11.NET_WM_ICON);
    }

    XFlush(_glfw.x11.display);
}