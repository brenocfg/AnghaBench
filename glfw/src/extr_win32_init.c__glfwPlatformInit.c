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
struct TYPE_3__ {int /*<<< orphan*/  foregroundLockTimeout; } ;
struct TYPE_4__ {TYPE_1__ win32; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 ; 
 int GLFW_FALSE ; 
 int GLFW_TRUE ; 
 scalar_t__ IsWindows8Point1OrGreater () ; 
 scalar_t__ IsWindowsVistaOrGreater () ; 
 int /*<<< orphan*/  PROCESS_PER_MONITOR_DPI_AWARE ; 
 int /*<<< orphan*/  SPIF_SENDCHANGE ; 
 int /*<<< orphan*/  SPI_GETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SPI_SETFOREGROUNDLOCKTIMEOUT ; 
 int /*<<< orphan*/  SetProcessDPIAware () ; 
 int /*<<< orphan*/  SetProcessDpiAwareness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetProcessDpiAwarenessContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemParametersInfoW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UIntToPtr (int /*<<< orphan*/ ) ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInitJoysticksWin32 () ; 
 int /*<<< orphan*/  _glfwInitTimerWin32 () ; 
 scalar_t__ _glfwIsWindows10CreatorsUpdateOrGreaterWin32 () ; 
 int /*<<< orphan*/  _glfwPollMonitorsWin32 () ; 
 int /*<<< orphan*/  _glfwRegisterWindowClassWin32 () ; 
 int /*<<< orphan*/  _glfwUpdateKeyNamesWin32 () ; 
 int /*<<< orphan*/  createHelperWindow () ; 
 int /*<<< orphan*/  createKeyTables () ; 
 int /*<<< orphan*/  loadLibraries () ; 

int _glfwPlatformInit(void)
{
    // To make SetForegroundWindow work as we want, we need to fiddle
    // with the FOREGROUNDLOCKTIMEOUT system setting (we do this as early
    // as possible in the hope of still being the foreground process)
    SystemParametersInfoW(SPI_GETFOREGROUNDLOCKTIMEOUT, 0,
                          &_glfw.win32.foregroundLockTimeout, 0);
    SystemParametersInfoW(SPI_SETFOREGROUNDLOCKTIMEOUT, 0, UIntToPtr(0),
                          SPIF_SENDCHANGE);

    if (!loadLibraries())
        return GLFW_FALSE;

    createKeyTables();
    _glfwUpdateKeyNamesWin32();

    if (_glfwIsWindows10CreatorsUpdateOrGreaterWin32())
        SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    else if (IsWindows8Point1OrGreater())
        SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
    else if (IsWindowsVistaOrGreater())
        SetProcessDPIAware();

    if (!_glfwRegisterWindowClassWin32())
        return GLFW_FALSE;

    if (!createHelperWindow())
        return GLFW_FALSE;

    _glfwInitTimerWin32();
    _glfwInitJoysticksWin32();

    _glfwPollMonitorsWin32();
    return GLFW_TRUE;
}