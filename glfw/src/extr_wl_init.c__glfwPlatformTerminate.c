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
struct TYPE_8__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_7__ {int /*<<< orphan*/ * handle; scalar_t__ context; scalar_t__ state; scalar_t__ keymap; scalar_t__ composeState; } ;
struct TYPE_6__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_9__ {scalar_t__ timerfd; scalar_t__ cursorTimerfd; scalar_t__ clipboardSendString; scalar_t__ clipboardString; scalar_t__ display; scalar_t__ registry; scalar_t__ idleInhibitManager; scalar_t__ pointerConstraints; scalar_t__ relativePointerManager; scalar_t__ seat; scalar_t__ keyboard; scalar_t__ pointer; scalar_t__ dataDeviceManager; scalar_t__ dataOffer; scalar_t__ dataDevice; scalar_t__ dataSource; scalar_t__ wmBase; scalar_t__ decorationManager; scalar_t__ viewporter; scalar_t__ shm; scalar_t__ compositor; scalar_t__ subcompositor; scalar_t__ cursorSurface; TYPE_3__ cursor; scalar_t__ cursorThemeHiDPI; scalar_t__ cursorTheme; TYPE_2__ xkb; TYPE_1__ egl; } ;
struct TYPE_10__ {TYPE_4__ wl; } ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  _glfwTerminateEGL () ; 
 int /*<<< orphan*/  _glfwTerminateJoysticksLinux () ; 
 int /*<<< orphan*/  _glfw_dlclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  wl_compositor_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_cursor_theme_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_data_device_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_data_device_manager_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_data_offer_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_data_source_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_flush (scalar_t__) ; 
 int /*<<< orphan*/  wl_keyboard_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_pointer_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_registry_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_seat_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_shm_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_subcompositor_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wl_surface_destroy (scalar_t__) ; 
 int /*<<< orphan*/  wp_viewporter_destroy (scalar_t__) ; 
 int /*<<< orphan*/  xdg_wm_base_destroy (scalar_t__) ; 
 int /*<<< orphan*/  xkb_compose_state_unref (scalar_t__) ; 
 int /*<<< orphan*/  xkb_context_unref (scalar_t__) ; 
 int /*<<< orphan*/  xkb_keymap_unref (scalar_t__) ; 
 int /*<<< orphan*/  xkb_state_unref (scalar_t__) ; 
 int /*<<< orphan*/  zwp_idle_inhibit_manager_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zwp_pointer_constraints_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zwp_relative_pointer_manager_v1_destroy (scalar_t__) ; 
 int /*<<< orphan*/  zxdg_decoration_manager_v1_destroy (scalar_t__) ; 

void _glfwPlatformTerminate(void)
{
#ifdef __linux__
    _glfwTerminateJoysticksLinux();
#endif
    _glfwTerminateEGL();
    if (_glfw.wl.egl.handle)
    {
        _glfw_dlclose(_glfw.wl.egl.handle);
        _glfw.wl.egl.handle = NULL;
    }

#ifdef HAVE_XKBCOMMON_COMPOSE_H
    if (_glfw.wl.xkb.composeState)
        xkb_compose_state_unref(_glfw.wl.xkb.composeState);
#endif
    if (_glfw.wl.xkb.keymap)
        xkb_keymap_unref(_glfw.wl.xkb.keymap);
    if (_glfw.wl.xkb.state)
        xkb_state_unref(_glfw.wl.xkb.state);
    if (_glfw.wl.xkb.context)
        xkb_context_unref(_glfw.wl.xkb.context);
    if (_glfw.wl.xkb.handle)
    {
        _glfw_dlclose(_glfw.wl.xkb.handle);
        _glfw.wl.xkb.handle = NULL;
    }

    if (_glfw.wl.cursorTheme)
        wl_cursor_theme_destroy(_glfw.wl.cursorTheme);
    if (_glfw.wl.cursorThemeHiDPI)
        wl_cursor_theme_destroy(_glfw.wl.cursorThemeHiDPI);
    if (_glfw.wl.cursor.handle)
    {
        _glfw_dlclose(_glfw.wl.cursor.handle);
        _glfw.wl.cursor.handle = NULL;
    }

    if (_glfw.wl.cursorSurface)
        wl_surface_destroy(_glfw.wl.cursorSurface);
    if (_glfw.wl.subcompositor)
        wl_subcompositor_destroy(_glfw.wl.subcompositor);
    if (_glfw.wl.compositor)
        wl_compositor_destroy(_glfw.wl.compositor);
    if (_glfw.wl.shm)
        wl_shm_destroy(_glfw.wl.shm);
    if (_glfw.wl.viewporter)
        wp_viewporter_destroy(_glfw.wl.viewporter);
    if (_glfw.wl.decorationManager)
        zxdg_decoration_manager_v1_destroy(_glfw.wl.decorationManager);
    if (_glfw.wl.wmBase)
        xdg_wm_base_destroy(_glfw.wl.wmBase);
    if (_glfw.wl.dataSource)
        wl_data_source_destroy(_glfw.wl.dataSource);
    if (_glfw.wl.dataDevice)
        wl_data_device_destroy(_glfw.wl.dataDevice);
    if (_glfw.wl.dataOffer)
        wl_data_offer_destroy(_glfw.wl.dataOffer);
    if (_glfw.wl.dataDeviceManager)
        wl_data_device_manager_destroy(_glfw.wl.dataDeviceManager);
    if (_glfw.wl.pointer)
        wl_pointer_destroy(_glfw.wl.pointer);
    if (_glfw.wl.keyboard)
        wl_keyboard_destroy(_glfw.wl.keyboard);
    if (_glfw.wl.seat)
        wl_seat_destroy(_glfw.wl.seat);
    if (_glfw.wl.relativePointerManager)
        zwp_relative_pointer_manager_v1_destroy(_glfw.wl.relativePointerManager);
    if (_glfw.wl.pointerConstraints)
        zwp_pointer_constraints_v1_destroy(_glfw.wl.pointerConstraints);
    if (_glfw.wl.idleInhibitManager)
        zwp_idle_inhibit_manager_v1_destroy(_glfw.wl.idleInhibitManager);
    if (_glfw.wl.registry)
        wl_registry_destroy(_glfw.wl.registry);
    if (_glfw.wl.display)
    {
        wl_display_flush(_glfw.wl.display);
        wl_display_disconnect(_glfw.wl.display);
    }

    if (_glfw.wl.timerfd >= 0)
        close(_glfw.wl.timerfd);
    if (_glfw.wl.cursorTimerfd >= 0)
        close(_glfw.wl.cursorTimerfd);

    if (_glfw.wl.clipboardString)
        free(_glfw.wl.clipboardString);
    if (_glfw.wl.clipboardSendString)
        free(_glfw.wl.clipboardSendString);
}