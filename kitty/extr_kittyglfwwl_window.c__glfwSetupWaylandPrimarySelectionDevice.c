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
struct TYPE_3__ {scalar_t__ primarySelectionDevice; int /*<<< orphan*/  seat; int /*<<< orphan*/  primarySelectionDeviceManager; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  primary_selection_device_listener ; 
 scalar_t__ zwp_primary_selection_device_manager_v1_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwp_primary_selection_device_v1_add_listener (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void _glfwSetupWaylandPrimarySelectionDevice() {
    _glfw.wl.primarySelectionDevice = zwp_primary_selection_device_manager_v1_get_device(_glfw.wl.primarySelectionDeviceManager, _glfw.wl.seat);
    if (_glfw.wl.primarySelectionDevice) zwp_primary_selection_device_v1_add_listener(_glfw.wl.primarySelectionDevice, &primary_selection_device_listener, NULL);
}