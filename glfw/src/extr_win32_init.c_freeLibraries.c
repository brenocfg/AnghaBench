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
struct TYPE_16__ {scalar_t__ instance; } ;
struct TYPE_15__ {scalar_t__ instance; } ;
struct TYPE_14__ {scalar_t__ instance; } ;
struct TYPE_13__ {scalar_t__ instance; } ;
struct TYPE_12__ {scalar_t__ instance; } ;
struct TYPE_11__ {scalar_t__ instance; } ;
struct TYPE_10__ {scalar_t__ instance; } ;
struct TYPE_17__ {TYPE_7__ ntdll; TYPE_6__ shcore; TYPE_5__ dwmapi; TYPE_4__ user32; TYPE_3__ winmm; TYPE_2__ dinput8; TYPE_1__ xinput; } ;
struct TYPE_18__ {TYPE_8__ win32; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 TYPE_9__ _glfw ; 

__attribute__((used)) static void freeLibraries(void)
{
    if (_glfw.win32.xinput.instance)
        FreeLibrary(_glfw.win32.xinput.instance);

    if (_glfw.win32.dinput8.instance)
        FreeLibrary(_glfw.win32.dinput8.instance);

    if (_glfw.win32.winmm.instance)
        FreeLibrary(_glfw.win32.winmm.instance);

    if (_glfw.win32.user32.instance)
        FreeLibrary(_glfw.win32.user32.instance);

    if (_glfw.win32.dwmapi.instance)
        FreeLibrary(_glfw.win32.dwmapi.instance);

    if (_glfw.win32.shcore.instance)
        FreeLibrary(_glfw.win32.shcore.instance);

    if (_glfw.win32.ntdll.instance)
        FreeLibrary(_glfw.win32.ntdll.instance);
}