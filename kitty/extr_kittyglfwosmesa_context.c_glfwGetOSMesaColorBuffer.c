#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_2__ osmesa; } ;
struct TYPE_6__ {TYPE_1__ context; } ;
typedef  TYPE_3__ _GLFWwindow ;
typedef  int GLint ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  OSMesaGetColorBuffer (int /*<<< orphan*/ ,int*,int*,int*,void**) ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int) ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int glfwGetOSMesaColorBuffer(GLFWwindow* handle, int* width,
                                     int* height, int* format, void** buffer)
{
    void* mesaBuffer;
    GLint mesaWidth, mesaHeight, mesaFormat;
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(GLFW_FALSE);

    if (!OSMesaGetColorBuffer(window->context.osmesa.handle,
                              &mesaWidth, &mesaHeight,
                              &mesaFormat, &mesaBuffer))
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "OSMesa: Failed to retrieve color buffer");
        return GLFW_FALSE;
    }

    if (width)
        *width = mesaWidth;
    if (height)
        *height = mesaHeight;
    if (format)
        *format = mesaFormat;
    if (buffer)
        *buffer = mesaBuffer;

    return GLFW_TRUE;
}