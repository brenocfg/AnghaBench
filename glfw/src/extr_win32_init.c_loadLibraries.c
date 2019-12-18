#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {void* instance; scalar_t__ RtlVerifyVersionInfo_; } ;
struct TYPE_15__ {void* instance; scalar_t__ GetDpiForMonitor_; scalar_t__ SetProcessDpiAwareness_; } ;
struct TYPE_14__ {void* instance; scalar_t__ EnableBlurBehindWindow; scalar_t__ Flush; scalar_t__ IsCompositionEnabled; } ;
struct TYPE_13__ {void* instance; scalar_t__ GetState; scalar_t__ GetCapabilities; } ;
struct TYPE_12__ {void* instance; scalar_t__ Create; } ;
struct TYPE_11__ {void* instance; scalar_t__ AdjustWindowRectExForDpi_; scalar_t__ GetDpiForWindow_; scalar_t__ SetProcessDpiAwarenessContext_; scalar_t__ EnableNonClientDpiScaling_; scalar_t__ ChangeWindowMessageFilterEx_; scalar_t__ SetProcessDPIAware_; } ;
struct TYPE_10__ {void* instance; scalar_t__ GetTime; } ;
struct TYPE_17__ {TYPE_7__ ntdll; TYPE_6__ shcore; TYPE_5__ dwmapi; TYPE_4__ xinput; TYPE_3__ dinput8; TYPE_2__ user32; TYPE_1__ winmm; } ;
struct TYPE_18__ {TYPE_8__ win32; } ;
typedef  scalar_t__ PFN_timeGetTime ;
typedef  scalar_t__ PFN_XInputGetState ;
typedef  scalar_t__ PFN_XInputGetCapabilities ;
typedef  scalar_t__ PFN_SetProcessDpiAwarenessContext ;
typedef  scalar_t__ PFN_SetProcessDpiAwareness ;
typedef  scalar_t__ PFN_SetProcessDPIAware ;
typedef  scalar_t__ PFN_RtlVerifyVersionInfo ;
typedef  scalar_t__ PFN_GetDpiForWindow ;
typedef  scalar_t__ PFN_GetDpiForMonitor ;
typedef  scalar_t__ PFN_EnableNonClientDpiScaling ;
typedef  scalar_t__ PFN_DwmIsCompositionEnabled ;
typedef  scalar_t__ PFN_DwmFlush ;
typedef  scalar_t__ PFN_DwmEnableBlurBehindWindow ;
typedef  scalar_t__ PFN_DirectInput8Create ;
typedef  scalar_t__ PFN_ChangeWindowMessageFilterEx ;
typedef  scalar_t__ PFN_AdjustWindowRectExForDpi ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ GetProcAddress (void*,char*) ; 
 void* LoadLibraryA (char const*) ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwInputErrorWin32 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static GLFWbool loadLibraries(void)
{
    _glfw.win32.winmm.instance = LoadLibraryA("winmm.dll");
    if (!_glfw.win32.winmm.instance)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "Win32: Failed to load winmm.dll");
        return GLFW_FALSE;
    }

    _glfw.win32.winmm.GetTime = (PFN_timeGetTime)
        GetProcAddress(_glfw.win32.winmm.instance, "timeGetTime");

    _glfw.win32.user32.instance = LoadLibraryA("user32.dll");
    if (!_glfw.win32.user32.instance)
    {
        _glfwInputErrorWin32(GLFW_PLATFORM_ERROR,
                             "Win32: Failed to load user32.dll");
        return GLFW_FALSE;
    }

    _glfw.win32.user32.SetProcessDPIAware_ = (PFN_SetProcessDPIAware)
        GetProcAddress(_glfw.win32.user32.instance, "SetProcessDPIAware");
    _glfw.win32.user32.ChangeWindowMessageFilterEx_ = (PFN_ChangeWindowMessageFilterEx)
        GetProcAddress(_glfw.win32.user32.instance, "ChangeWindowMessageFilterEx");
    _glfw.win32.user32.EnableNonClientDpiScaling_ = (PFN_EnableNonClientDpiScaling)
        GetProcAddress(_glfw.win32.user32.instance, "EnableNonClientDpiScaling");
    _glfw.win32.user32.SetProcessDpiAwarenessContext_ = (PFN_SetProcessDpiAwarenessContext)
        GetProcAddress(_glfw.win32.user32.instance, "SetProcessDpiAwarenessContext");
    _glfw.win32.user32.GetDpiForWindow_ = (PFN_GetDpiForWindow)
        GetProcAddress(_glfw.win32.user32.instance, "GetDpiForWindow");
    _glfw.win32.user32.AdjustWindowRectExForDpi_ = (PFN_AdjustWindowRectExForDpi)
        GetProcAddress(_glfw.win32.user32.instance, "AdjustWindowRectExForDpi");

    _glfw.win32.dinput8.instance = LoadLibraryA("dinput8.dll");
    if (_glfw.win32.dinput8.instance)
    {
        _glfw.win32.dinput8.Create = (PFN_DirectInput8Create)
            GetProcAddress(_glfw.win32.dinput8.instance, "DirectInput8Create");
    }

    {
        int i;
        const char* names[] =
        {
            "xinput1_4.dll",
            "xinput1_3.dll",
            "xinput9_1_0.dll",
            "xinput1_2.dll",
            "xinput1_1.dll",
            NULL
        };

        for (i = 0;  names[i];  i++)
        {
            _glfw.win32.xinput.instance = LoadLibraryA(names[i]);
            if (_glfw.win32.xinput.instance)
            {
                _glfw.win32.xinput.GetCapabilities = (PFN_XInputGetCapabilities)
                    GetProcAddress(_glfw.win32.xinput.instance, "XInputGetCapabilities");
                _glfw.win32.xinput.GetState = (PFN_XInputGetState)
                    GetProcAddress(_glfw.win32.xinput.instance, "XInputGetState");

                break;
            }
        }
    }

    _glfw.win32.dwmapi.instance = LoadLibraryA("dwmapi.dll");
    if (_glfw.win32.dwmapi.instance)
    {
        _glfw.win32.dwmapi.IsCompositionEnabled = (PFN_DwmIsCompositionEnabled)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmIsCompositionEnabled");
        _glfw.win32.dwmapi.Flush = (PFN_DwmFlush)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmFlush");
        _glfw.win32.dwmapi.EnableBlurBehindWindow = (PFN_DwmEnableBlurBehindWindow)
            GetProcAddress(_glfw.win32.dwmapi.instance, "DwmEnableBlurBehindWindow");
    }

    _glfw.win32.shcore.instance = LoadLibraryA("shcore.dll");
    if (_glfw.win32.shcore.instance)
    {
        _glfw.win32.shcore.SetProcessDpiAwareness_ = (PFN_SetProcessDpiAwareness)
            GetProcAddress(_glfw.win32.shcore.instance, "SetProcessDpiAwareness");
        _glfw.win32.shcore.GetDpiForMonitor_ = (PFN_GetDpiForMonitor)
            GetProcAddress(_glfw.win32.shcore.instance, "GetDpiForMonitor");
    }

    _glfw.win32.ntdll.instance = LoadLibraryA("ntdll.dll");
    if (_glfw.win32.ntdll.instance)
    {
        _glfw.win32.ntdll.RtlVerifyVersionInfo_ = (PFN_RtlVerifyVersionInfo)
            GetProcAddress(_glfw.win32.ntdll.instance, "RtlVerifyVersionInfo");
    }

    return GLFW_TRUE;
}