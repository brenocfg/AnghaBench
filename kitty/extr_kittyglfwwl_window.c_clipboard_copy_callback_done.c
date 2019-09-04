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
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_callback {int dummy; } ;
struct TYPE_3__ {scalar_t__ dataDevice; scalar_t__ dataSourceForClipboard; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  wl_callback_destroy (struct wl_callback*) ; 
 int /*<<< orphan*/  wl_data_device_set_selection (scalar_t__,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
clipboard_copy_callback_done(void *data, struct wl_callback *callback, uint32_t serial) {
    if (_glfw.wl.dataDevice && data == (void*)_glfw.wl.dataSourceForClipboard) {
        wl_data_device_set_selection(_glfw.wl.dataDevice, data, serial);
    }
    wl_callback_destroy(callback);
}