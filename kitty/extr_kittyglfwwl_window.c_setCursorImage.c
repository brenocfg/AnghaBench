#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wl_surface {int dummy; } ;
struct wl_cursor_image {int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ delay; } ;
struct wl_buffer {int dummy; } ;
struct TYPE_8__ {size_t currentImage; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  yhot; int /*<<< orphan*/  xhot; TYPE_1__* cursor; struct wl_buffer* buffer; } ;
typedef  TYPE_3__ _GLFWcursorWayland ;
struct TYPE_7__ {int /*<<< orphan*/  pointerSerial; int /*<<< orphan*/  pointer; int /*<<< orphan*/  cursorAnimationTimer; int /*<<< orphan*/  eventLoopData; struct wl_surface* cursorSurface; } ;
struct TYPE_9__ {TYPE_2__ wl; } ;
struct TYPE_6__ {struct wl_cursor_image** images; } ;

/* Variables and functions */
 TYPE_5__ _glfw ; 
 int /*<<< orphan*/  changeTimerInterval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double) ; 
 int /*<<< orphan*/  toggleTimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct wl_buffer* wl_cursor_image_get_buffer (struct wl_cursor_image*) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_attach (struct wl_surface*,struct wl_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 
 int /*<<< orphan*/  wl_surface_damage (struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
setCursorImage(_GLFWcursorWayland* cursorWayland)
{
    struct wl_cursor_image* image;
    struct wl_buffer* buffer;
    struct wl_surface* surface = _glfw.wl.cursorSurface;

    if (!cursorWayland->cursor) {
        buffer = cursorWayland->buffer;
        toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, 0);
    } else
    {
        image = cursorWayland->cursor->images[cursorWayland->currentImage];
        buffer = wl_cursor_image_get_buffer(image);
        if (image->delay) {
            changeTimerInterval(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, ((double)image->delay) / 1000.0);
            toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, 1);
        } else {
            toggleTimer(&_glfw.wl.eventLoopData, _glfw.wl.cursorAnimationTimer, 0);
        }

        if (!buffer)
            return;

        cursorWayland->width = image->width;
        cursorWayland->height = image->height;
        cursorWayland->xhot = image->hotspot_x;
        cursorWayland->yhot = image->hotspot_y;
    }

    wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial,
                          surface,
                          cursorWayland->xhot,
                          cursorWayland->yhot);
    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_damage(surface, 0, 0,
                      cursorWayland->width, cursorWayland->height);
    wl_surface_commit(surface);
}