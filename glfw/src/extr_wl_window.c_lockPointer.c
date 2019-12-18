#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct zwp_relative_pointer_v1 {int dummy; } ;
struct zwp_locked_pointer_v1 {int dummy; } ;
struct TYPE_9__ {struct zwp_locked_pointer_v1* lockedPointer; struct zwp_relative_pointer_v1* relativePointer; } ;
struct TYPE_10__ {TYPE_1__ pointerLock; int /*<<< orphan*/  surface; } ;
struct TYPE_12__ {TYPE_2__ wl; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_11__ {int /*<<< orphan*/  serial; int /*<<< orphan*/  pointer; int /*<<< orphan*/  pointerConstraints; int /*<<< orphan*/  relativePointerManager; } ;
struct TYPE_13__ {TYPE_3__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lockedPointerListener ; 
 int /*<<< orphan*/  relativePointerListener ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_locked_pointer_v1_add_listener (struct zwp_locked_pointer_v1*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 struct zwp_locked_pointer_v1* zwp_pointer_constraints_v1_lock_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct zwp_relative_pointer_v1* zwp_relative_pointer_manager_v1_get_relative_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_relative_pointer_v1_add_listener (struct zwp_relative_pointer_v1*,int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void lockPointer(_GLFWwindow* window)
{
    struct zwp_relative_pointer_v1* relativePointer;
    struct zwp_locked_pointer_v1* lockedPointer;

    if (!_glfw.wl.relativePointerManager)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: no relative pointer manager");
        return;
    }

    relativePointer =
        zwp_relative_pointer_manager_v1_get_relative_pointer(
            _glfw.wl.relativePointerManager,
            _glfw.wl.pointer);
    zwp_relative_pointer_v1_add_listener(relativePointer,
                                         &relativePointerListener,
                                         window);

    lockedPointer =
        zwp_pointer_constraints_v1_lock_pointer(
            _glfw.wl.pointerConstraints,
            window->wl.surface,
            _glfw.wl.pointer,
            NULL,
            ZWP_POINTER_CONSTRAINTS_V1_LIFETIME_PERSISTENT);
    zwp_locked_pointer_v1_add_listener(lockedPointer,
                                       &lockedPointerListener,
                                       window);

    window->wl.pointerLock.relativePointer = relativePointer;
    window->wl.pointerLock.lockedPointer = lockedPointer;

    wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.serial,
                          NULL, 0, 0);
}