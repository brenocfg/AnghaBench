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
struct wl_keyboard {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  xkb; } ;
struct TYPE_4__ {TYPE_1__ wl; } ;

/* Variables and functions */
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  glfw_xkb_update_modifiers (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keyboardHandleModifiers(void* data,
                                    struct wl_keyboard* keyboard,
                                    uint32_t serial,
                                    uint32_t modsDepressed,
                                    uint32_t modsLatched,
                                    uint32_t modsLocked,
                                    uint32_t group)
{
    glfw_xkb_update_modifiers(&_glfw.wl.xkb, modsDepressed, modsLatched, modsLocked, 0, 0, group);
}