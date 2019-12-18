#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  instanceName; int /*<<< orphan*/  className; } ;
struct TYPE_6__ {int /*<<< orphan*/  frameName; } ;
struct TYPE_7__ {TYPE_3__ x11; TYPE_1__ ns; } ;
struct TYPE_9__ {TYPE_2__ window; } ;
struct TYPE_10__ {TYPE_4__ hints; } ;

/* Variables and functions */
#define  GLFW_COCOA_FRAME_NAME 130 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
#define  GLFW_X11_CLASS_NAME 129 
#define  GLFW_X11_INSTANCE_NAME 128 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

void glfwWindowHintString(int hint, const char* value)
{
    assert(value != NULL);

    _GLFW_REQUIRE_INIT();

    switch (hint)
    {
        case GLFW_COCOA_FRAME_NAME:
            strncpy(_glfw.hints.window.ns.frameName, value,
                    sizeof(_glfw.hints.window.ns.frameName) - 1);
            return;
        case GLFW_X11_CLASS_NAME:
            strncpy(_glfw.hints.window.x11.className, value,
                    sizeof(_glfw.hints.window.x11.className) - 1);
            return;
        case GLFW_X11_INSTANCE_NAME:
            strncpy(_glfw.hints.window.x11.instanceName, value,
                    sizeof(_glfw.hints.window.x11.instanceName) - 1);
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint string 0x%08X", hint);
}