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
struct TYPE_3__ {int /*<<< orphan*/  serial; int /*<<< orphan*/ * dataSource; int /*<<< orphan*/  dataDevice; int /*<<< orphan*/ * clipboardSendString; int /*<<< orphan*/  dataDeviceManager; int /*<<< orphan*/  clipboardSendSize; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dataSourceListener ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/ * wl_data_device_manager_create_data_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_data_device_set_selection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_data_source_add_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_data_source_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_data_source_offer (int /*<<< orphan*/ *,char*) ; 

void _glfwPlatformSetClipboardString(const char* string)
{
    if (_glfw.wl.dataSource)
    {
        wl_data_source_destroy(_glfw.wl.dataSource);
        _glfw.wl.dataSource = NULL;
    }

    if (_glfw.wl.clipboardSendString)
    {
        free(_glfw.wl.clipboardSendString);
        _glfw.wl.clipboardSendString = NULL;
    }

    _glfw.wl.clipboardSendString = strdup(string);
    if (!_glfw.wl.clipboardSendString)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Impossible to allocate clipboard string");
        return;
    }
    _glfw.wl.clipboardSendSize = strlen(string);
    _glfw.wl.dataSource =
        wl_data_device_manager_create_data_source(_glfw.wl.dataDeviceManager);
    if (!_glfw.wl.dataSource)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Impossible to create clipboard source");
        free(_glfw.wl.clipboardSendString);
        return;
    }
    wl_data_source_add_listener(_glfw.wl.dataSource,
                                &dataSourceListener,
                                NULL);
    wl_data_source_offer(_glfw.wl.dataSource, "text/plain;charset=utf-8");
    wl_data_device_set_selection(_glfw.wl.dataDevice,
                                 _glfw.wl.dataSource,
                                 _glfw.wl.serial);
}