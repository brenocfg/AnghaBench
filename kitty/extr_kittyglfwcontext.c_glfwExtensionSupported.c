#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int major; int (* extensionSupported ) (char const*) ;scalar_t__ (* GetString ) (int /*<<< orphan*/ ) ;scalar_t__ (* GetStringi ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* GetIntegerv ) (int /*<<< orphan*/ ,int*) ;} ;
struct TYPE_6__ {TYPE_1__ context; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  contextSlot; } ;
typedef  int GLint ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  GLFW_NO_CURRENT_CONTEXT ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* _glfwPlatformGetTls (int /*<<< orphan*/ *) ; 
 scalar_t__ _glfwStringInExtensionString (char const*,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (char const*) ; 

int glfwExtensionSupported(const char* extension)
{
    _GLFWwindow* window;
    assert(extension != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(GLFW_FALSE);

    window = _glfwPlatformGetTls(&_glfw.contextSlot);
    if (!window)
    {
        _glfwInputError(GLFW_NO_CURRENT_CONTEXT,
                        "Cannot query extension without a current OpenGL or OpenGL ES context");
        return GLFW_FALSE;
    }

    if (*extension == '\0')
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Extension name cannot be an empty string");
        return GLFW_FALSE;
    }

    if (window->context.major >= 3)
    {
        int i;
        GLint count;

        // Check if extension is in the modern OpenGL extensions string list

        window->context.GetIntegerv(GL_NUM_EXTENSIONS, &count);

        for (i = 0;  i < count;  i++)
        {
            const char* en = (const char*)
                window->context.GetStringi(GL_EXTENSIONS, i);
            if (!en)
            {
                _glfwInputError(GLFW_PLATFORM_ERROR,
                                "Extension string retrieval is broken");
                return GLFW_FALSE;
            }

            if (strcmp(en, extension) == 0)
                return GLFW_TRUE;
        }
    }
    else
    {
        // Check if extension is in the old style OpenGL extensions string

        const char* extensions = (const char*)
            window->context.GetString(GL_EXTENSIONS);
        if (!extensions)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Extension string retrieval is broken");
            return GLFW_FALSE;
        }

        if (_glfwStringInExtensionString(extension, extensions))
            return GLFW_TRUE;
    }

    // Check if extension is in the platform-specific string
    return window->context.extensionSupported(extension);
}