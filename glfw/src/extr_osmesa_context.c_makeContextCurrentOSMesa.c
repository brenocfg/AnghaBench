#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  handle; } ;
struct TYPE_9__ {TYPE_1__ osmesa; } ;
struct TYPE_10__ {TYPE_2__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_11__ {int /*<<< orphan*/  contextSlot; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  OSMesaMakeCurrent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwPlatformGetFramebufferSize (TYPE_3__*,int*,int*) ; 
 int /*<<< orphan*/  _glfwPlatformSetTls (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * calloc (int,size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void makeContextCurrentOSMesa(_GLFWwindow* window)
{
    if (window)
    {
        int width, height;
        _glfwPlatformGetFramebufferSize(window, &width, &height);

        // Check to see if we need to allocate a new buffer
        if ((window->context.osmesa.buffer == NULL) ||
            (width != window->context.osmesa.width) ||
            (height != window->context.osmesa.height))
        {
            free(window->context.osmesa.buffer);

            // Allocate the new buffer (width * height * 8-bit RGBA)
            window->context.osmesa.buffer = calloc(4, (size_t) width * height);
            window->context.osmesa.width  = width;
            window->context.osmesa.height = height;
        }

        if (!OSMesaMakeCurrent(window->context.osmesa.handle,
                               window->context.osmesa.buffer,
                               GL_UNSIGNED_BYTE,
                               width, height))
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "OSMesa: Failed to make context current");
            return;
        }
    }

    _glfwPlatformSetTls(&_glfw.contextSlot, window);
}