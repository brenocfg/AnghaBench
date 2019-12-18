#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_8__ {TYPE_2__ x11; } ;
typedef  TYPE_3__ _GLFWcursor ;
struct TYPE_6__ {int /*<<< orphan*/  display; } ;
struct TYPE_9__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int GLFW_ARROW_CURSOR ; 
 int GLFW_CROSSHAIR_CURSOR ; 
 int GLFW_FALSE ; 
 int GLFW_HAND_CURSOR ; 
 int GLFW_HRESIZE_CURSOR ; 
 int GLFW_IBEAM_CURSOR ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 int GLFW_VRESIZE_CURSOR ; 
 int XC_crosshair ; 
 int XC_hand2 ; 
 int XC_left_ptr ; 
 int XC_sb_h_double_arrow ; 
 int XC_sb_v_double_arrow ; 
 int XC_xterm ; 
 int /*<<< orphan*/  XCreateFontCursor (int /*<<< orphan*/ ,int) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, int shape)
{
    int native = 0;

    if (shape == GLFW_ARROW_CURSOR)
        native = XC_left_ptr;
    else if (shape == GLFW_IBEAM_CURSOR)
        native = XC_xterm;
    else if (shape == GLFW_CROSSHAIR_CURSOR)
        native = XC_crosshair;
    else if (shape == GLFW_HAND_CURSOR)
        native = XC_hand2;
    else if (shape == GLFW_HRESIZE_CURSOR)
        native = XC_sb_h_double_arrow;
    else if (shape == GLFW_VRESIZE_CURSOR)
        native = XC_sb_v_double_arrow;
    else
        return GLFW_FALSE;

    cursor->x11.handle = XCreateFontCursor(_glfw.x11.display, native);
    if (!cursor->x11.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "X11: Failed to create standard cursor");
        return GLFW_FALSE;
    }

    return GLFW_TRUE;
}