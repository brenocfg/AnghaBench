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
struct wl_keyboard {int dummy; } ;
typedef  void* int32_t ;
struct TYPE_3__ {void* keyboardRepeatDelay; void* keyboardRepeatRate; struct wl_keyboard* keyboard; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 

__attribute__((used)) static void keyboardHandleRepeatInfo(void* data,
                                     struct wl_keyboard* keyboard,
                                     int32_t rate,
                                     int32_t delay)
{
    if (keyboard != _glfw.wl.keyboard)
        return;

    _glfw.wl.keyboardRepeatRate = rate;
    _glfw.wl.keyboardRepeatDelay = delay;
}