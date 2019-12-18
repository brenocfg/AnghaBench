#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  protocols ;
struct TYPE_24__ {char const* instanceName; char const* className; } ;
struct TYPE_27__ {int width; int height; char const* title; TYPE_1__ x11; scalar_t__ maximized; scalar_t__ floating; int /*<<< orphan*/  decorated; scalar_t__ scaleToMonitor; } ;
typedef  TYPE_4__ _GLFWwndconfig ;
struct TYPE_25__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  ypos; int /*<<< orphan*/  xpos; int /*<<< orphan*/  handle; int /*<<< orphan*/  ic; int /*<<< orphan*/  maximized; int /*<<< orphan*/  colormap; int /*<<< orphan*/  transparent; } ;
struct TYPE_28__ {TYPE_2__ x11; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_5__ _GLFWwindow ;
struct TYPE_29__ {char* res_name; char* res_class; int /*<<< orphan*/  initial_state; int /*<<< orphan*/  flags; } ;
typedef  TYPE_6__ XWMHints ;
struct TYPE_30__ {int event_mask; scalar_t__ border_pixel; int /*<<< orphan*/  colormap; } ;
typedef  TYPE_7__ XSetWindowAttributes ;
typedef  int /*<<< orphan*/  XPointer ;
typedef  TYPE_6__ XClassHint ;
typedef  int /*<<< orphan*/  Visual ;
struct TYPE_26__ {int contentScaleX; int contentScaleY; scalar_t__ im; scalar_t__ XdndAware; int /*<<< orphan*/  display; scalar_t__ NET_WM_WINDOW_TYPE; scalar_t__ NET_WM_WINDOW_TYPE_NORMAL; scalar_t__ NET_WM_PID; scalar_t__ NET_WM_PING; scalar_t__ WM_DELETE_WINDOW; scalar_t__ NET_WM_STATE; scalar_t__ NET_WM_STATE_MAXIMIZED_HORZ; scalar_t__ NET_WM_STATE_MAXIMIZED_VERT; scalar_t__ NET_WM_STATE_ABOVE; int /*<<< orphan*/  context; int /*<<< orphan*/  root; } ;
struct TYPE_23__ {TYPE_3__ x11; } ;
typedef  int /*<<< orphan*/  GLFWbool ;
typedef  scalar_t__ Atom ;

/* Variables and functions */
 int /*<<< orphan*/  AllocNone ; 
 int ButtonPressMask ; 
 int ButtonReleaseMask ; 
 unsigned long CWBorderPixel ; 
 unsigned long CWColormap ; 
 unsigned long CWEventMask ; 
 int EnterWindowMask ; 
 int ExposureMask ; 
 int FocusChangeMask ; 
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/  InputOutput ; 
 int KeyPressMask ; 
 int KeyReleaseMask ; 
 int LeaveWindowMask ; 
 int /*<<< orphan*/  NormalState ; 
 int PointerMotionMask ; 
 int /*<<< orphan*/  PropModeReplace ; 
 int PropertyChangeMask ; 
 int /*<<< orphan*/  StateHint ; 
 int StructureNotifyMask ; 
 int VisibilityChangeMask ; 
 int /*<<< orphan*/  XA_ATOM ; 
 int /*<<< orphan*/  XA_CARDINAL ; 
 TYPE_6__* XAllocClassHint () ; 
 TYPE_6__* XAllocWMHints () ; 
 int /*<<< orphan*/  XChangeProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  XCreateColormap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCreateIC (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XCreateWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long const,TYPE_7__*) ; 
 int /*<<< orphan*/  XFree (TYPE_6__*) ; 
 int XIMPreeditNothing ; 
 int XIMStatusNothing ; 
 int /*<<< orphan*/  XNClientWindow ; 
 int /*<<< orphan*/  XNFocusWindow ; 
 int /*<<< orphan*/  XNInputStyle ; 
 int /*<<< orphan*/  XSaveContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSetClassHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMHints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  XSetWMProtocols (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ _GLFW_XDND_VERSION ; 
 TYPE_16__ _glfw ; 
 int /*<<< orphan*/  _glfwGrabErrorHandlerX11 () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwInputErrorX11 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _glfwIsVisualTransparentX11 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowPos (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowSize (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowDecorated (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowTitle (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  _glfwReleaseErrorHandlerX11 () ; 
 char* getenv (char*) ; 
 long getpid () ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  updateNormalHints (TYPE_5__*,int,int) ; 

__attribute__((used)) static GLFWbool createNativeWindow(_GLFWwindow* window,
                                   const _GLFWwndconfig* wndconfig,
                                   Visual* visual, int depth)
{
    int width = wndconfig->width;
    int height = wndconfig->height;

    if (wndconfig->scaleToMonitor)
    {
        width *= _glfw.x11.contentScaleX;
        height *= _glfw.x11.contentScaleY;
    }

    // Create a colormap based on the visual used by the current context
    window->x11.colormap = XCreateColormap(_glfw.x11.display,
                                           _glfw.x11.root,
                                           visual,
                                           AllocNone);

    window->x11.transparent = _glfwIsVisualTransparentX11(visual);

    // Create the actual window
    {
        XSetWindowAttributes wa;
        const unsigned long wamask = CWBorderPixel | CWColormap | CWEventMask;

        wa.colormap = window->x11.colormap;
        wa.border_pixel = 0;
        wa.event_mask = StructureNotifyMask | KeyPressMask | KeyReleaseMask |
                        PointerMotionMask | ButtonPressMask | ButtonReleaseMask |
                        ExposureMask | FocusChangeMask | VisibilityChangeMask |
                        EnterWindowMask | LeaveWindowMask | PropertyChangeMask;

        _glfwGrabErrorHandlerX11();

        window->x11.handle = XCreateWindow(_glfw.x11.display,
                                           _glfw.x11.root,
                                           0, 0,
                                           width, height,
                                           0,      // Border width
                                           depth,  // Color depth
                                           InputOutput,
                                           visual,
                                           wamask,
                                           &wa);

        _glfwReleaseErrorHandlerX11();

        if (!window->x11.handle)
        {
            _glfwInputErrorX11(GLFW_PLATFORM_ERROR,
                               "X11: Failed to create window");
            return GLFW_FALSE;
        }

        XSaveContext(_glfw.x11.display,
                     window->x11.handle,
                     _glfw.x11.context,
                     (XPointer) window);
    }

    if (!wndconfig->decorated)
        _glfwPlatformSetWindowDecorated(window, GLFW_FALSE);

    if (_glfw.x11.NET_WM_STATE && !window->monitor)
    {
        Atom states[3];
        int count = 0;

        if (wndconfig->floating)
        {
            if (_glfw.x11.NET_WM_STATE_ABOVE)
                states[count++] = _glfw.x11.NET_WM_STATE_ABOVE;
        }

        if (wndconfig->maximized)
        {
            if (_glfw.x11.NET_WM_STATE_MAXIMIZED_VERT &&
                _glfw.x11.NET_WM_STATE_MAXIMIZED_HORZ)
            {
                states[count++] = _glfw.x11.NET_WM_STATE_MAXIMIZED_VERT;
                states[count++] = _glfw.x11.NET_WM_STATE_MAXIMIZED_HORZ;
                window->x11.maximized = GLFW_TRUE;
            }
        }

        if (count)
        {
            XChangeProperty(_glfw.x11.display, window->x11.handle,
                            _glfw.x11.NET_WM_STATE, XA_ATOM, 32,
                            PropModeReplace, (unsigned char*) &states, count);
        }
    }

    // Declare the WM protocols supported by GLFW
    {
        Atom protocols[] =
        {
            _glfw.x11.WM_DELETE_WINDOW,
            _glfw.x11.NET_WM_PING
        };

        XSetWMProtocols(_glfw.x11.display, window->x11.handle,
                        protocols, sizeof(protocols) / sizeof(Atom));
    }

    // Declare our PID
    {
        const long pid = getpid();

        XChangeProperty(_glfw.x11.display,  window->x11.handle,
                        _glfw.x11.NET_WM_PID, XA_CARDINAL, 32,
                        PropModeReplace,
                        (unsigned char*) &pid, 1);
    }

    if (_glfw.x11.NET_WM_WINDOW_TYPE && _glfw.x11.NET_WM_WINDOW_TYPE_NORMAL)
    {
        Atom type = _glfw.x11.NET_WM_WINDOW_TYPE_NORMAL;
        XChangeProperty(_glfw.x11.display,  window->x11.handle,
                        _glfw.x11.NET_WM_WINDOW_TYPE, XA_ATOM, 32,
                        PropModeReplace, (unsigned char*) &type, 1);
    }

    // Set ICCCM WM_HINTS property
    {
        XWMHints* hints = XAllocWMHints();
        if (!hints)
        {
            _glfwInputError(GLFW_OUT_OF_MEMORY,
                            "X11: Failed to allocate WM hints");
            return GLFW_FALSE;
        }

        hints->flags = StateHint;
        hints->initial_state = NormalState;

        XSetWMHints(_glfw.x11.display, window->x11.handle, hints);
        XFree(hints);
    }

    updateNormalHints(window, width, height);

    // Set ICCCM WM_CLASS property
    {
        XClassHint* hint = XAllocClassHint();

        if (strlen(wndconfig->x11.instanceName) &&
            strlen(wndconfig->x11.className))
        {
            hint->res_name = (char*) wndconfig->x11.instanceName;
            hint->res_class = (char*) wndconfig->x11.className;
        }
        else
        {
            const char* resourceName = getenv("RESOURCE_NAME");
            if (resourceName && strlen(resourceName))
                hint->res_name = (char*) resourceName;
            else if (strlen(wndconfig->title))
                hint->res_name = (char*) wndconfig->title;
            else
                hint->res_name = (char*) "glfw-application";

            if (strlen(wndconfig->title))
                hint->res_class = (char*) wndconfig->title;
            else
                hint->res_class = (char*) "GLFW-Application";
        }

        XSetClassHint(_glfw.x11.display, window->x11.handle, hint);
        XFree(hint);
    }

    // Announce support for Xdnd (drag and drop)
    {
        const Atom version = _GLFW_XDND_VERSION;
        XChangeProperty(_glfw.x11.display, window->x11.handle,
                        _glfw.x11.XdndAware, XA_ATOM, 32,
                        PropModeReplace, (unsigned char*) &version, 1);
    }

    _glfwPlatformSetWindowTitle(window, wndconfig->title);

    if (_glfw.x11.im)
    {
        window->x11.ic = XCreateIC(_glfw.x11.im,
                                   XNInputStyle,
                                   XIMPreeditNothing | XIMStatusNothing,
                                   XNClientWindow,
                                   window->x11.handle,
                                   XNFocusWindow,
                                   window->x11.handle,
                                   NULL);
    }

    _glfwPlatformGetWindowPos(window, &window->x11.xpos, &window->x11.ypos);
    _glfwPlatformGetWindowSize(window, &window->x11.width, &window->x11.height);

    return GLFW_TRUE;
}