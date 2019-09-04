#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ibus; int /*<<< orphan*/ * context; } ;
typedef  TYPE_1__ _GLFWXKBData ;

/* Variables and functions */
 int /*<<< orphan*/  glfw_ibus_terminate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_keyboard_data (TYPE_1__*) ; 
 int /*<<< orphan*/  xkb_context_unref (int /*<<< orphan*/ *) ; 

void
glfw_xkb_release(_GLFWXKBData *xkb) {
    release_keyboard_data(xkb);
    if (xkb->context) {
        xkb_context_unref(xkb->context);
        xkb->context = NULL;
    }
    glfw_ibus_terminate(&xkb->ibus);
}