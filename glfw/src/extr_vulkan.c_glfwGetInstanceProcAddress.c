#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VkInstance ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {TYPE_1__ vk; } ;
typedef  int /*<<< orphan*/ * GLFWvkproc ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_LOADER ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInitVulkan (int /*<<< orphan*/ ) ; 
 scalar_t__ _glfw_dlsym (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ vkGetInstanceProcAddr (int /*<<< orphan*/ ,char const*) ; 

GLFWvkproc glfwGetInstanceProcAddress(VkInstance instance,
                                              const char* procname)
{
    GLFWvkproc proc;
    assert(procname != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (!_glfwInitVulkan(_GLFW_REQUIRE_LOADER))
        return NULL;

    proc = (GLFWvkproc) vkGetInstanceProcAddr(instance, procname);
#if defined(_GLFW_VULKAN_STATIC)
    if (!proc)
    {
        if (strcmp(procname, "vkGetInstanceProcAddr") == 0)
            return (GLFWvkproc) vkGetInstanceProcAddr;
    }
#else
    if (!proc)
        proc = (GLFWvkproc) _glfw_dlsym(_glfw.vk.handle, procname);
#endif

    return proc;
}