#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_8__ {int mask_len; unsigned char* mask; int /*<<< orphan*/  deviceid; } ;
typedef  TYPE_3__ XIEventMask ;
struct TYPE_6__ {scalar_t__ available; } ;
struct TYPE_7__ {int /*<<< orphan*/  restoreCursorPosY; int /*<<< orphan*/  restoreCursorPosX; int /*<<< orphan*/  display; int /*<<< orphan*/ * disabledCursorWindow; int /*<<< orphan*/  root; TYPE_1__ xi; } ;
struct TYPE_9__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentTime ; 
 int /*<<< orphan*/  XIAllMasterDevices ; 
 int /*<<< orphan*/  XISelectEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  XUngrabPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ _glfw ; 
 int /*<<< orphan*/  _glfwPlatformSetCursorPos (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  updateCursorImage (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void enableCursor(_GLFWwindow* window)
{
    if (_glfw.x11.xi.available)
    {
        XIEventMask em;
        unsigned char mask[] = { 0 };

        em.deviceid = XIAllMasterDevices;
        em.mask_len = sizeof(mask);
        em.mask = mask;

        XISelectEvents(_glfw.x11.display, _glfw.x11.root, &em, 1);
    }

    _glfw.x11.disabledCursorWindow = NULL;
    XUngrabPointer(_glfw.x11.display, CurrentTime);
    _glfwPlatformSetCursorPos(window,
                              _glfw.x11.restoreCursorPosX,
                              _glfw.x11.restoreCursorPosY);
    updateCursorImage(window);
}