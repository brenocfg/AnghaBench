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
struct TYPE_3__ {scalar_t__ dataDevice; int /*<<< orphan*/  seat; int /*<<< orphan*/  dataDeviceManager; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  data_device_listener ; 
 int /*<<< orphan*/  wl_data_device_add_listener (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ wl_data_device_manager_get_data_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void _glfwSetupWaylandDataDevice() {
    _glfw.wl.dataDevice = wl_data_device_manager_get_data_device(_glfw.wl.dataDeviceManager, _glfw.wl.seat);
    if (_glfw.wl.dataDevice) wl_data_device_add_listener(_glfw.wl.dataDevice, &data_device_listener, NULL);
}