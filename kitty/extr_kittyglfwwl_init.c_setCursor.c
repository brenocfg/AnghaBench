#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wl_surface {int dummy; } ;
struct wl_cursor_image {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  hotspot_y; int /*<<< orphan*/  hotspot_x; } ;
struct wl_cursor {struct wl_cursor_image** images; } ;
struct wl_buffer {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  pointerSerial; int /*<<< orphan*/  pointer; struct wl_surface* cursorSurface; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;
typedef  int /*<<< orphan*/  GLFWCursorShape ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 struct wl_cursor* _glfwLoadCursor (int /*<<< orphan*/ ) ; 
 struct wl_buffer* wl_cursor_image_get_buffer (struct wl_cursor_image*) ; 
 int /*<<< orphan*/  wl_pointer_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_attach (struct wl_surface*,struct wl_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (struct wl_surface*) ; 
 int /*<<< orphan*/  wl_surface_damage (struct wl_surface*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setCursor(GLFWCursorShape shape)
{
    struct wl_buffer* buffer;
    struct wl_cursor* cursor;
    struct wl_cursor_image* image;
    struct wl_surface* surface = _glfw.wl.cursorSurface;

    cursor = _glfwLoadCursor(shape);
    if (!cursor) return;
    // TODO: handle animated cursors too.
    image = cursor->images[0];

    if (!image)
        return;

    buffer = wl_cursor_image_get_buffer(image);
    if (!buffer)
        return;
    wl_pointer_set_cursor(_glfw.wl.pointer, _glfw.wl.pointerSerial,
                          surface,
                          image->hotspot_x,
                          image->hotspot_y);
    wl_surface_attach(surface, buffer, 0, 0);
    wl_surface_damage(surface, 0, 0,
                      image->width, image->height);
    wl_surface_commit(surface);
}