#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  transparent; int /*<<< orphan*/  overrideRedirect; } ;
struct TYPE_18__ {TYPE_4__ x11; TYPE_2__* monitor; } ;
typedef  TYPE_6__ _GLFWwindow ;
struct TYPE_19__ {int /*<<< orphan*/  override_redirect; } ;
typedef  TYPE_7__ XSetWindowAttributes ;
struct TYPE_15__ {scalar_t__ available; } ;
struct TYPE_17__ {int NET_WM_STATE_FULLSCREEN; scalar_t__ NET_WM_BYPASS_COMPOSITOR; int /*<<< orphan*/  display; scalar_t__ NET_WM_STATE; scalar_t__ NET_WM_FULLSCREEN_MONITORS; TYPE_3__ xinerama; } ;
struct TYPE_13__ {int index; } ;
struct TYPE_14__ {TYPE_1__ x11; } ;
struct TYPE_12__ {TYPE_5__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  CWOverrideRedirect ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int /*<<< orphan*/  True ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XChangeWindowAttributes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  XDeleteProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int _NET_WM_STATE_ADD ; 
 int _NET_WM_STATE_REMOVE ; 
 TYPE_10__ _glfw ; 
 int /*<<< orphan*/  sendEventToWM (TYPE_6__*,scalar_t__,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void updateWindowMode(_GLFWwindow* window)
{
    if (window->monitor)
    {
        if (_glfw.x11.xinerama.available &&
            _glfw.x11.NET_WM_FULLSCREEN_MONITORS)
        {
            sendEventToWM(window,
                          _glfw.x11.NET_WM_FULLSCREEN_MONITORS,
                          window->monitor->x11.index,
                          window->monitor->x11.index,
                          window->monitor->x11.index,
                          window->monitor->x11.index,
                          0);
        }

        if (_glfw.x11.NET_WM_STATE && _glfw.x11.NET_WM_STATE_FULLSCREEN)
        {
            sendEventToWM(window,
                          _glfw.x11.NET_WM_STATE,
                          _NET_WM_STATE_ADD,
                          _glfw.x11.NET_WM_STATE_FULLSCREEN,
                          0, 1, 0);
        }
        else
        {
            // This is the butcher's way of removing window decorations
            // Setting the override-redirect attribute on a window makes the
            // window manager ignore the window completely (ICCCM, section 4)
            // The good thing is that this makes undecorated full screen windows
            // easy to do; the bad thing is that we have to do everything
            // manually and some things (like iconify/restore) won't work at
            // all, as those are tasks usually performed by the window manager

            XSetWindowAttributes attributes;
            attributes.override_redirect = True;
            XChangeWindowAttributes(_glfw.x11.display,
                                    window->x11.handle,
                                    CWOverrideRedirect,
                                    &attributes);

            window->x11.overrideRedirect = GLFW_TRUE;
        }

        // Enable compositor bypass
        if (!window->x11.transparent)
        {
            const unsigned long value = 1;

            XChangeProperty(_glfw.x11.display,  window->x11.handle,
                            _glfw.x11.NET_WM_BYPASS_COMPOSITOR, XA_CARDINAL, 32,
                            PropModeReplace, (unsigned char*) &value, 1);
        }
    }
    else
    {
        if (_glfw.x11.xinerama.available &&
            _glfw.x11.NET_WM_FULLSCREEN_MONITORS)
        {
            XDeleteProperty(_glfw.x11.display, window->x11.handle,
                            _glfw.x11.NET_WM_FULLSCREEN_MONITORS);
        }

        if (_glfw.x11.NET_WM_STATE && _glfw.x11.NET_WM_STATE_FULLSCREEN)
        {
            sendEventToWM(window,
                          _glfw.x11.NET_WM_STATE,
                          _NET_WM_STATE_REMOVE,
                          _glfw.x11.NET_WM_STATE_FULLSCREEN,
                          0, 1, 0);
        }
        else
        {
            XSetWindowAttributes attributes;
            attributes.override_redirect = False;
            XChangeWindowAttributes(_glfw.x11.display,
                                    window->x11.handle,
                                    CWOverrideRedirect,
                                    &attributes);

            window->x11.overrideRedirect = GLFW_FALSE;
        }

        // Disable compositor bypass
        if (!window->x11.transparent)
        {
            XDeleteProperty(_glfw.x11.display, window->x11.handle,
                            _glfw.x11.NET_WM_BYPASS_COMPOSITOR);
        }
    }
}