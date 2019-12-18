#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  context; void* handle; scalar_t__ compose_state_get_one_sym; scalar_t__ compose_state_get_status; scalar_t__ compose_state_feed; scalar_t__ compose_state_unref; scalar_t__ compose_state_new; scalar_t__ compose_table_unref; scalar_t__ compose_table_new_from_locale; scalar_t__ state_serialize_mods; scalar_t__ state_update_mask; scalar_t__ state_key_get_syms; scalar_t__ state_unref; scalar_t__ state_new; scalar_t__ keymap_key_repeats; scalar_t__ keymap_mod_get_index; scalar_t__ keymap_unref; scalar_t__ keymap_new_from_string; scalar_t__ context_unref; scalar_t__ context_new; } ;
struct TYPE_8__ {void* handle; scalar_t__ window_resize; scalar_t__ window_destroy; scalar_t__ window_create; } ;
struct TYPE_7__ {void* handle; scalar_t__ image_get_buffer; scalar_t__ theme_get_cursor; scalar_t__ theme_destroy; scalar_t__ theme_load; } ;
struct TYPE_9__ {int timerfd; int seatVersion; int clipboardSize; int /*<<< orphan*/  clipboardString; int /*<<< orphan*/  dataDevice; scalar_t__ seat; scalar_t__ dataDeviceManager; void* cursorTimerfd; int /*<<< orphan*/  compositor; int /*<<< orphan*/  cursorSurface; scalar_t__ shm; void* cursorThemeHiDPI; void* cursorTheme; scalar_t__ pointer; int /*<<< orphan*/  wmBase; int /*<<< orphan*/  display; TYPE_1__ xkb; int /*<<< orphan*/  registry; TYPE_3__ egl; TYPE_2__ cursor; } ;
struct TYPE_10__ {TYPE_4__ wl; } ;
typedef  scalar_t__ PFN_xkb_state_update_mask ;
typedef  scalar_t__ PFN_xkb_state_unref ;
typedef  scalar_t__ PFN_xkb_state_serialize_mods ;
typedef  scalar_t__ PFN_xkb_state_new ;
typedef  scalar_t__ PFN_xkb_state_key_get_syms ;
typedef  scalar_t__ PFN_xkb_keymap_unref ;
typedef  scalar_t__ PFN_xkb_keymap_new_from_string ;
typedef  scalar_t__ PFN_xkb_keymap_mod_get_index ;
typedef  scalar_t__ PFN_xkb_keymap_key_repeats ;
typedef  scalar_t__ PFN_xkb_context_unref ;
typedef  scalar_t__ PFN_xkb_context_new ;
typedef  scalar_t__ PFN_xkb_compose_table_unref ;
typedef  scalar_t__ PFN_xkb_compose_table_new_from_locale ;
typedef  scalar_t__ PFN_xkb_compose_state_unref ;
typedef  scalar_t__ PFN_xkb_compose_state_new ;
typedef  scalar_t__ PFN_xkb_compose_state_get_status ;
typedef  scalar_t__ PFN_xkb_compose_state_get_one_sym ;
typedef  scalar_t__ PFN_xkb_compose_state_feed ;
typedef  scalar_t__ PFN_wl_egl_window_resize ;
typedef  scalar_t__ PFN_wl_egl_window_destroy ;
typedef  scalar_t__ PFN_wl_egl_window_create ;
typedef  scalar_t__ PFN_wl_cursor_theme_load ;
typedef  scalar_t__ PFN_wl_cursor_theme_get_cursor ;
typedef  scalar_t__ PFN_wl_cursor_theme_destroy ;
typedef  scalar_t__ PFN_wl_cursor_image_get_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int GLFW_TRUE ; 
 long INT_MAX ; 
 int /*<<< orphan*/  TFD_CLOEXEC ; 
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwInitJoysticksLinux () ; 
 int /*<<< orphan*/  _glfwInitTimerPOSIX () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 void* _glfw_dlopen (char*) ; 
 scalar_t__ _glfw_dlsym (void*,char*) ; 
 int /*<<< orphan*/  createKeyTables () ; 
 int /*<<< orphan*/  dataDeviceListener ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  registryListener ; 
 long strtol (char const*,char**,int) ; 
 void* timerfd_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_compositor_create_surface (int /*<<< orphan*/ ) ; 
 void* wl_cursor_theme_load (char const*,int,scalar_t__) ; 
 int /*<<< orphan*/  wl_data_device_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_data_device_manager_get_data_device (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wl_display_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_display_get_registry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_registry_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xkb_context_new (int /*<<< orphan*/ ) ; 

int _glfwPlatformInit(void)
{
    const char *cursorTheme;
    const char *cursorSizeStr;
    char *cursorSizeEnd;
    long cursorSizeLong;
    int cursorSize;

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

    _glfw.wl.xkb.handle = _glfw_dlopen("libxkbcommon.so.0");
    if (!_glfw.wl.xkb.handle)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to open libxkbcommon");
        return GLFW_FALSE;
    }

    _glfw.wl.xkb.context_new = (PFN_xkb_context_new)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_context_new");
    _glfw.wl.xkb.context_unref = (PFN_xkb_context_unref)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_context_unref");
    _glfw.wl.xkb.keymap_new_from_string = (PFN_xkb_keymap_new_from_string)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_keymap_new_from_string");
    _glfw.wl.xkb.keymap_unref = (PFN_xkb_keymap_unref)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_keymap_unref");
    _glfw.wl.xkb.keymap_mod_get_index = (PFN_xkb_keymap_mod_get_index)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_keymap_mod_get_index");
    _glfw.wl.xkb.keymap_key_repeats = (PFN_xkb_keymap_key_repeats)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_keymap_key_repeats");
    _glfw.wl.xkb.state_new = (PFN_xkb_state_new)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_state_new");
    _glfw.wl.xkb.state_unref = (PFN_xkb_state_unref)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_state_unref");
    _glfw.wl.xkb.state_key_get_syms = (PFN_xkb_state_key_get_syms)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_state_key_get_syms");
    _glfw.wl.xkb.state_update_mask = (PFN_xkb_state_update_mask)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_state_update_mask");
    _glfw.wl.xkb.state_serialize_mods = (PFN_xkb_state_serialize_mods)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_state_serialize_mods");

#ifdef HAVE_XKBCOMMON_COMPOSE_H
    _glfw.wl.xkb.compose_table_new_from_locale = (PFN_xkb_compose_table_new_from_locale)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_table_new_from_locale");
    _glfw.wl.xkb.compose_table_unref = (PFN_xkb_compose_table_unref)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_table_unref");
    _glfw.wl.xkb.compose_state_new = (PFN_xkb_compose_state_new)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_state_new");
    _glfw.wl.xkb.compose_state_unref = (PFN_xkb_compose_state_unref)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_state_unref");
    _glfw.wl.xkb.compose_state_feed = (PFN_xkb_compose_state_feed)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_state_feed");
    _glfw.wl.xkb.compose_state_get_status = (PFN_xkb_compose_state_get_status)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_state_get_status");
    _glfw.wl.xkb.compose_state_get_one_sym = (PFN_xkb_compose_state_get_one_sym)
        _glfw_dlsym(_glfw.wl.xkb.handle, "xkb_compose_state_get_one_sym");
#endif

    _glfw.wl.display = wl_display_connect(NULL);
    if (!_glfw.wl.display)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to connect to display");
        return GLFW_FALSE;
    }

    _glfw.wl.registry = wl_display_get_registry(_glfw.wl.display);
    wl_registry_add_listener(_glfw.wl.registry, &registryListener, NULL);

    createKeyTables();

    _glfw.wl.xkb.context = xkb_context_new(0);
    if (!_glfw.wl.xkb.context)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to initialize xkb context");
        return GLFW_FALSE;
    }

    // Sync so we got all registry objects
    wl_display_roundtrip(_glfw.wl.display);

    // Sync so we got all initial output events
    wl_display_roundtrip(_glfw.wl.display);

#ifdef __linux__
    if (!_glfwInitJoysticksLinux())
        return GLFW_FALSE;
#endif

    _glfwInitTimerPOSIX();

    _glfw.wl.timerfd = -1;
    if (_glfw.wl.seatVersion >= 4)
        _glfw.wl.timerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);

    if (!_glfw.wl.wmBase)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Failed to find xdg-shell in your compositor");
        return GLFW_FALSE;
    }

    if (_glfw.wl.pointer && _glfw.wl.shm)
    {
        cursorTheme = getenv("XCURSOR_THEME");
        cursorSizeStr = getenv("XCURSOR_SIZE");
        cursorSize = 32;
        if (cursorSizeStr)
        {
            errno = 0;
            cursorSizeLong = strtol(cursorSizeStr, &cursorSizeEnd, 10);
            if (!*cursorSizeEnd && !errno && cursorSizeLong > 0 && cursorSizeLong <= INT_MAX)
                cursorSize = (int)cursorSizeLong;
        }
        _glfw.wl.cursorTheme =
            wl_cursor_theme_load(cursorTheme, cursorSize, _glfw.wl.shm);
        if (!_glfw.wl.cursorTheme)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Unable to load default cursor theme");
            return GLFW_FALSE;
        }
        // If this happens to be NULL, we just fallback to the scale=1 version.
        _glfw.wl.cursorThemeHiDPI =
            wl_cursor_theme_load(cursorTheme, 2 * cursorSize, _glfw.wl.shm);
        _glfw.wl.cursorSurface =
            wl_compositor_create_surface(_glfw.wl.compositor);
        _glfw.wl.cursorTimerfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC);
    }

    if (_glfw.wl.seat && _glfw.wl.dataDeviceManager)
    {
        _glfw.wl.dataDevice =
            wl_data_device_manager_get_data_device(_glfw.wl.dataDeviceManager,
                                                   _glfw.wl.seat);
        wl_data_device_add_listener(_glfw.wl.dataDevice, &dataDeviceListener, NULL);
        _glfw.wl.clipboardString = malloc(4096);
        if (!_glfw.wl.clipboardString)
        {
            _glfwInputError(GLFW_PLATFORM_ERROR,
                            "Wayland: Unable to allocate clipboard memory");
            return GLFW_FALSE;
        }
        _glfw.wl.clipboardSize = 4096;
    }

    return GLFW_TRUE;
}