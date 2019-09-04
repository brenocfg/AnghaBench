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
struct TYPE_3__ {int /*<<< orphan*/  dataDevice; int /*<<< orphan*/  seat; int /*<<< orphan*/  dataDeviceManager; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline GLFWbool _glfwEnsureDataDevice() {
    if (!_glfw.wl.dataDeviceManager)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Cannot use clipboard, data device manager is not ready");
        return GLFW_FALSE;
    }

    if (!_glfw.wl.dataDevice)
    {
        if (!_glfw.wl.seat)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Cannot use clipboard, seat is not ready");
            return GLFW_FALSE;
        }
        if (!_glfw.wl.dataDevice)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                    "Wayland: Cannot use clipboard, failed to create data device");
            return GLFW_FALSE;
        }
    }
    return GLFW_TRUE;
}