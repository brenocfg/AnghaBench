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
struct TYPE_3__ {int /*<<< orphan*/  rawInput; int /*<<< orphan*/  clipboardString; int /*<<< orphan*/  foregroundLockTimeout; scalar_t__ helperWindowHandle; scalar_t__ deviceNotificationHandle; } ;
struct TYPE_4__ {TYPE_1__ win32; } ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  SPIF_SENDCHANGE ; 
 int /*<<< orphan*/  SPI_SETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIntToPtr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnregisterDeviceNotification (scalar_t__) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwTerminateEGL () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticksWin32 () ; 
 int /*<<< orphan*/  _glfwTerminateWGL () ; 
 int /*<<< orphan*/  _glfwUnregisterWindowClassWin32 () ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeLibraries () ; 

void _glfwPlatformTerminate(void)
{
    if (_glfw.win32.deviceNotificationHandle)
        UnregisterDeviceNotification(_glfw.win32.deviceNotificationHandle);

    if (_glfw.win32.helperWindowHandle)
        DestroyWindow(_glfw.win32.helperWindowHandle);

    _glfwUnregisterWindowClassWin32();

    // Restore previous foreground lock timeout system setting
    SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0,
                          UIntToPtr(_glfw.win32.foregroundLockTimeout),
                          SPIF_SENDCHANGE);

    free(_glfw.win32.clipboardString);
    free(_glfw.win32.rawInput);

    _glfwTerminateWGL();
    _glfwTerminateEGL();

    _glfwTerminateJoysticksWin32();

    freeLibraries();
}