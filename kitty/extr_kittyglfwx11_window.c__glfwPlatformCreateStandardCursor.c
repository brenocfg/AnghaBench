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
typedef  int GLFWCursorShape ;

/* Variables and functions */
#define  GLFW_ARROW_CURSOR 138 
#define  GLFW_CROSSHAIR_CURSOR 137 
 int GLFW_FALSE ; 
#define  GLFW_HAND_CURSOR 136 
#define  GLFW_HRESIZE_CURSOR 135 
#define  GLFW_IBEAM_CURSOR 134 
#define  GLFW_INVALID_CURSOR 133 
#define  GLFW_NE_RESIZE_CURSOR 132 
#define  GLFW_NW_RESIZE_CURSOR 131 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
#define  GLFW_SE_RESIZE_CURSOR 130 
#define  GLFW_SW_RESIZE_CURSOR 129 
 int GLFW_TRUE ; 
#define  GLFW_VRESIZE_CURSOR 128 
 int XC_arrow ; 
 int XC_bottom_left_corner ; 
 int XC_bottom_right_corner ; 
 int XC_crosshair ; 
 int XC_hand2 ; 
 int XC_sb_h_double_arrow ; 
 int XC_sb_v_double_arrow ; 
 int XC_top_left_corner ; 
 int XC_top_right_corner ; 
 int XC_xterm ; 
 int /*<<< orphan*/  XCreateFontCursor (int /*<<< orphan*/ ,int) ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 

int _glfwPlatformCreateStandardCursor(_GLFWcursor* cursor, GLFWCursorShape shape)
{
    int native = 0;
#define C(name, val) case name: native = val; break;
    switch(shape) {
        C(GLFW_ARROW_CURSOR, XC_arrow);
        C(GLFW_IBEAM_CURSOR, XC_xterm);
        C(GLFW_CROSSHAIR_CURSOR, XC_crosshair);
        C(GLFW_HAND_CURSOR, XC_hand2);
        C(GLFW_HRESIZE_CURSOR, XC_sb_h_double_arrow);
        C(GLFW_VRESIZE_CURSOR, XC_sb_v_double_arrow);
        C(GLFW_NW_RESIZE_CURSOR, XC_top_left_corner);
        C(GLFW_NE_RESIZE_CURSOR, XC_top_right_corner);
        C(GLFW_SW_RESIZE_CURSOR, XC_bottom_left_corner);
        C(GLFW_SE_RESIZE_CURSOR, XC_bottom_right_corner);
        case GLFW_INVALID_CURSOR:
            return GLFW_FALSE;
    }
#undef C

    cursor->x11.handle = XCreateFontCursor(_glfw.x11.display, native);
    if (!cursor->x11.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "X11: Failed to create standard cursor");
        return GLFW_FALSE;
    }

    return GLFW_TRUE;
}