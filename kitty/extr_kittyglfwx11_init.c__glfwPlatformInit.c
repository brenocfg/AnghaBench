#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ inotify; } ;
struct TYPE_13__ {int /*<<< orphan*/ * wakeupFds; } ;
struct TYPE_11__ {TYPE_5__ eventLoopData; int /*<<< orphan*/  hiddenCursorHandle; int /*<<< orphan*/  helperWindowHandle; int /*<<< orphan*/  contentScaleY; int /*<<< orphan*/  contentScaleX; int /*<<< orphan*/  root; int /*<<< orphan*/  display; int /*<<< orphan*/  RESOURCE_MANAGER; int /*<<< orphan*/  context; int /*<<< orphan*/  screen; int /*<<< orphan*/  dbus; } ;
struct TYPE_9__ {scalar_t__ enableJoysticks; } ;
struct TYPE_10__ {TYPE_1__ init; } ;
struct TYPE_14__ {TYPE_4__ linjs; TYPE_3__ x11; TYPE_2__ hints; } ;

/* Variables and functions */
 int /*<<< orphan*/  ConnectionNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DefaultScreen (int /*<<< orphan*/ ) ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  PropertyChangeMask ; 
 int /*<<< orphan*/  RootWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XInitThreads () ; 
 int /*<<< orphan*/  XInternAtom (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XOpenDisplay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XSelectInput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XUniqueContext () ; 
 int /*<<< orphan*/  XrmInitialize () ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  _glfwGetSystemContentScaleX11 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _glfwInitJoysticksLinux () ; 
 int /*<<< orphan*/  _glfwInitTimerPOSIX () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  _glfwPollMonitorsX11 () ; 
 int /*<<< orphan*/  addWatch (TYPE_5__*,char*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  createHelperWindow () ; 
 int /*<<< orphan*/  createHiddenCursor () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  glfw_dbus_init (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  initExtensions () ; 
 int /*<<< orphan*/  initPollData (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe2 (int /*<<< orphan*/ *,int) ; 

int _glfwPlatformInit(void)
{
    XInitThreads();
    XrmInitialize();

    if (pipe2(_glfw.x11.eventLoopData.wakeupFds, O_CLOEXEC | O_NONBLOCK) != 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                "X11: failed to create self pipe");
        return GLFW_FALSE;
    }

    _glfw.x11.display = XOpenDisplay(NULL);
    if (!_glfw.x11.display)
    {
        const char* display = getenv("DISPLAY");
        if (display)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: Failed to open display %s", display);
        }
        else
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "X11: The DISPLAY environment variable is missing");
        }

        return GLFW_FALSE;
    }

    initPollData(&_glfw.x11.eventLoopData, _glfw.x11.eventLoopData.wakeupFds[0], ConnectionNumber(_glfw.x11.display));
    glfw_dbus_init(&_glfw.x11.dbus, &_glfw.x11.eventLoopData);

    _glfw.x11.screen = DefaultScreen(_glfw.x11.display);
    _glfw.x11.root = RootWindow(_glfw.x11.display, _glfw.x11.screen);
    _glfw.x11.context = XUniqueContext();
    _glfw.x11.RESOURCE_MANAGER = XInternAtom(_glfw.x11.display, "RESOURCE_MANAGER", True);
    XSelectInput(_glfw.x11.display, _glfw.x11.root, PropertyChangeMask);

    _glfwGetSystemContentScaleX11(&_glfw.x11.contentScaleX, &_glfw.x11.contentScaleY, GLFW_FALSE);

    if (!initExtensions())
        return GLFW_FALSE;

    _glfw.x11.helperWindowHandle = createHelperWindow();
    _glfw.x11.hiddenCursorHandle = createHiddenCursor();

#if defined(__linux__)
    if (_glfw.hints.init.enableJoysticks) {
        if (!_glfwInitJoysticksLinux())
            return GLFW_FALSE;
        if (_glfw.linjs.inotify > 0)
            addWatch(&_glfw.x11.eventLoopData, "joystick", _glfw.linjs.inotify, POLLIN, 1, NULL, NULL);
    }
#endif

    _glfwInitTimerPOSIX();

    _glfwPollMonitorsX11();
    return GLFW_TRUE;
}