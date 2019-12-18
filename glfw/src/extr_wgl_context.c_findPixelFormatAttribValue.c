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

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputErrorWin32 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int findPixelFormatAttribValue(const int* attribs,
                                      int attribCount,
                                      const int* values,
                                      int attrib)
{
    int i;

    for (i = 0;  i < attribCount;  i++)
    {
        if (attribs[i] == attrib)
            return values[i];
    }

    _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                         "WGL: Unknown pixel format attribute requested");
    return 0;
}