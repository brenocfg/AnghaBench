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
struct TYPE_3__ {int /*<<< orphan*/  ibus; int /*<<< orphan*/  context; } ;
typedef  TYPE_1__ _GLFWXKBData ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glfw_connect_to_ibus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_context_new (int /*<<< orphan*/ ) ; 

GLFWbool
glfw_xkb_create_context(_GLFWXKBData *xkb) {
    xkb->context = xkb_context_new(0);
    if (!xkb->context)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Failed to initialize XKB context");
        return GLFW_FALSE;
    }
    glfw_connect_to_ibus(&xkb->ibus);
    return GLFW_TRUE;
}