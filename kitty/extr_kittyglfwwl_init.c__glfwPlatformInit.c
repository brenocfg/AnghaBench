#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/ * wakeupFds; } ;
struct TYPE_14__ {void* keyRepeatTimer; } ;
struct TYPE_13__ {void* handle; scalar_t__ window_resize; scalar_t__ window_destroy; scalar_t__ window_create; } ;
struct TYPE_12__ {void* handle; scalar_t__ image_get_buffer; scalar_t__ theme_get_cursor; scalar_t__ theme_destroy; scalar_t__ theme_load; } ;
struct TYPE_17__ {int /*<<< orphan*/  compositor; int /*<<< orphan*/  cursorSurface; int /*<<< orphan*/  cursorTheme; scalar_t__ shm; int /*<<< orphan*/  display; int /*<<< orphan*/  xkb; int /*<<< orphan*/  registry; TYPE_7__ eventLoopData; void* cursorAnimationTimer; TYPE_3__ keyRepeatInfo; int /*<<< orphan*/  dbus; TYPE_2__ egl; TYPE_1__ cursor; } ;
struct TYPE_15__ {scalar_t__ enableJoysticks; } ;
struct TYPE_16__ {TYPE_4__ init; } ;
struct TYPE_11__ {TYPE_6__ wl; TYPE_5__ hints; } ;
typedef  scalar_t__ PFN_wl_egl_window_resize ;
typedef  scalar_t__ PFN_wl_egl_window_destroy ;
typedef  scalar_t__ PFN_wl_egl_window_create ;
typedef  scalar_t__ PFN_wl_cursor_theme_load ;
typedef  scalar_t__ PFN_wl_cursor_theme_get_cursor ;
typedef  scalar_t__ PFN_wl_cursor_theme_destroy ;
typedef  scalar_t__ PFN_wl_cursor_image_get_buffer ;

/* Variables and functions */
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 long INT_MAX ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 TYPE_10__ _glfw ; 
 int /*<<< orphan*/  _glfwInitJoysticksLinux () ; 
 int /*<<< orphan*/  _glfwInitTimerPOSIX () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 void* _glfw_dlopen (char*) ; 
 scalar_t__ _glfw_dlsym (void*,char*) ; 
 void* addTimer (TYPE_7__*,char*,double,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  animateCursorImage ; 
 int /*<<< orphan*/  dispatchPendingKeyRepeats ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  glfw_dbus_init (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  glfw_xkb_create_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  initPollData (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe2 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  registryListener ; 
 long strtol (char const*,char**,int) ; 
 int /*<<< orphan*/  wl_compositor_create_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_cursor_theme_load (char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  wl_display_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_display_get_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_get_registry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_registry_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int _glfwPlatformInit(void)
{
    if (pipe2(_glfw.wl.eventLoopData.wakeupFds, O_CLOEXEC | O_NONBLOCK) != 0)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                "Wayland: failed to create self pipe");
        return GLFW_FALSE;
    }

    _glfw.wl.cursor.handle = _glfw_dlopen("libwayland-cursor.so.0");
    if (!_glfw.wl.cursor.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to open libwayland-cursor");
        return GLFW_FALSE;
    }

    _glfw.wl.cursor.theme_load = (PFN_wl_cursor_theme_load)
        _glfw_dlsym(_glfw.wl.cursor.handle, "wl_cursor_theme_load");
    _glfw.wl.cursor.theme_destroy = (PFN_wl_cursor_theme_destroy)
        _glfw_dlsym(_glfw.wl.cursor.handle, "wl_cursor_theme_destroy");
    _glfw.wl.cursor.theme_get_cursor = (PFN_wl_cursor_theme_get_cursor)
        _glfw_dlsym(_glfw.wl.cursor.handle, "wl_cursor_theme_get_cursor");
    _glfw.wl.cursor.image_get_buffer = (PFN_wl_cursor_image_get_buffer)
        _glfw_dlsym(_glfw.wl.cursor.handle, "wl_cursor_image_get_buffer");

    _glfw.wl.egl.handle = _glfw_dlopen("libwayland-egl.so.1");
    if (!_glfw.wl.egl.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to open libwayland-egl");
        return GLFW_FALSE;
    }

    _glfw.wl.egl.window_create = (PFN_wl_egl_window_create)
        _glfw_dlsym(_glfw.wl.egl.handle, "wl_egl_window_create");
    _glfw.wl.egl.window_destroy = (PFN_wl_egl_window_destroy)
        _glfw_dlsym(_glfw.wl.egl.handle, "wl_egl_window_destroy");
    _glfw.wl.egl.window_resize = (PFN_wl_egl_window_resize)
        _glfw_dlsym(_glfw.wl.egl.handle, "wl_egl_window_resize");

    _glfw.wl.display = wl_display_connect(NULL);
    if (!_glfw.wl.display)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to connect to display");
        return GLFW_FALSE;
    }
    initPollData(&_glfw.wl.eventLoopData, _glfw.wl.eventLoopData.wakeupFds[0], wl_display_get_fd(_glfw.wl.display));
    glfw_dbus_init(&_glfw.wl.dbus, &_glfw.wl.eventLoopData);
    _glfw.wl.keyRepeatInfo.keyRepeatTimer = addTimer(&_glfw.wl.eventLoopData, "wayland-key-repeat", 0.5, 0, true, dispatchPendingKeyRepeats, NULL, NULL);
    _glfw.wl.cursorAnimationTimer = addTimer(&_glfw.wl.eventLoopData, "wayland-cursor-animation", 0.5, 0, true, animateCursorImage, NULL, NULL);

    _glfw.wl.registry = wl_display_get_registry(_glfw.wl.display);
    wl_registry_add_listener(_glfw.wl.registry, &registryListener, NULL);

    if (!glfw_xkb_create_context(&_glfw.wl.xkb)) return GLFW_FALSE;

    // Sync so we got all registry objects
    wl_display_roundtrip(_glfw.wl.display);

    // Sync so we got all initial output events
    wl_display_roundtrip(_glfw.wl.display);

#ifdef __linux__
    if (_glfw.hints.init.enableJoysticks) {
        if (!_glfwInitJoysticksLinux())
            return GLFW_FALSE;
    }
#endif

    _glfwInitTimerPOSIX();

    if (_glfw.wl.shm)
    {
        const char *cursorTheme = getenv("XCURSOR_THEME"), *cursorSizeStr = getenv("XCURSOR_SIZE");
        char *cursorSizeEnd;
        int cursorSize = 32;
        if (cursorSizeStr)
        {
            errno = 0;
            long cursorSizeLong = strtol(cursorSizeStr, &cursorSizeEnd, 10);
            if (!*cursorSizeEnd && !errno && cursorSizeLong > 0 && cursorSizeLong <= INT_MAX)
                cursorSize = (int)cursorSizeLong;
        }
        _glfw.wl.cursorTheme = wl_cursor_theme_load(cursorTheme, cursorSize, _glfw.wl.shm);
        if (!_glfw.wl.cursorTheme)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Unable to load default cursor theme");
            return GLFW_FALSE;
        }
        _glfw.wl.cursorSurface =
            wl_compositor_create_surface(_glfw.wl.compositor);
    }

    return GLFW_TRUE;
}