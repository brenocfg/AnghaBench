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
struct TYPE_16__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_15__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_14__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_13__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_12__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_11__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_10__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_17__ {scalar_t__ helperWindowHandle; TYPE_7__ xi; TYPE_6__ vidmode; TYPE_5__ xrender; TYPE_4__ xinerama; TYPE_3__ randr; TYPE_2__ xcursor; TYPE_1__ x11xcb; int /*<<< orphan*/ * display; int /*<<< orphan*/ * im; int /*<<< orphan*/  clipboardString; int /*<<< orphan*/  primarySelectionString; scalar_t__ hiddenCursorHandle; int /*<<< orphan*/  CLIPBOARD; } ;
struct TYPE_18__ {TYPE_8__ x11; } ;
typedef  scalar_t__ Cursor ;

/* Variables and functions */
 scalar_t__ None ; 
 int /*<<< orphan*/  XCloseDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCloseIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XDestroyWindow (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  XFreeCursor (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ XGetSelectionOwner (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwPushSelectionToManagerX11 () ; 
 int /*<<< orphan*/  _glfwTerminateEGL () ; 
 int /*<<< orphan*/  _glfwTerminateGLX () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticksLinux () ; 
 int /*<<< orphan*/  _glfw_dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void _glfwPlatformTerminate(void)
{
    if (_glfw.x11.helperWindowHandle)
    {
        if (XGetSelectionOwner(_glfw.x11.display, _glfw.x11.CLIPBOARD) ==
            _glfw.x11.helperWindowHandle)
        {
            _glfwPushSelectionToManagerX11();
        }

        XDestroyWindow(_glfw.x11.display, _glfw.x11.helperWindowHandle);
        _glfw.x11.helperWindowHandle = None;
    }

    if (_glfw.x11.hiddenCursorHandle)
    {
        XFreeCursor(_glfw.x11.display, _glfw.x11.hiddenCursorHandle);
        _glfw.x11.hiddenCursorHandle = (Cursor) 0;
    }

    free(_glfw.x11.primarySelectionString);
    free(_glfw.x11.clipboardString);

    if (_glfw.x11.im)
    {
        XCloseIM(_glfw.x11.im);
        _glfw.x11.im = NULL;
    }

    if (_glfw.x11.display)
    {
        XCloseDisplay(_glfw.x11.display);
        _glfw.x11.display = NULL;
    }

    if (_glfw.x11.x11xcb.handle)
    {
        _glfw_dlclose(_glfw.x11.x11xcb.handle);
        _glfw.x11.x11xcb.handle = NULL;
    }

    if (_glfw.x11.xcursor.handle)
    {
        _glfw_dlclose(_glfw.x11.xcursor.handle);
        _glfw.x11.xcursor.handle = NULL;
    }

    if (_glfw.x11.randr.handle)
    {
        _glfw_dlclose(_glfw.x11.randr.handle);
        _glfw.x11.randr.handle = NULL;
    }

    if (_glfw.x11.xinerama.handle)
    {
        _glfw_dlclose(_glfw.x11.xinerama.handle);
        _glfw.x11.xinerama.handle = NULL;
    }

    if (_glfw.x11.xrender.handle)
    {
        _glfw_dlclose(_glfw.x11.xrender.handle);
        _glfw.x11.xrender.handle = NULL;
    }

    if (_glfw.x11.vidmode.handle)
    {
        _glfw_dlclose(_glfw.x11.vidmode.handle);
        _glfw.x11.vidmode.handle = NULL;
    }

    if (_glfw.x11.xi.handle)
    {
        _glfw_dlclose(_glfw.x11.xi.handle);
        _glfw.x11.xi.handle = NULL;
    }

    // NOTE: These need to be unloaded after XCloseDisplay, as they register
    //       cleanup callbacks that get called by that function
    _glfwTerminateEGL();
    _glfwTerminateGLX();

#if defined(__linux__)
    _glfwTerminateJoysticksLinux();
#endif
}