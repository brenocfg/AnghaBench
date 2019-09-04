#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ id; struct TYPE_4__* next; } ;
typedef  TYPE_1__ _GLFWwindow ;
struct TYPE_5__ {scalar_t__ focusedWindowId; TYPE_1__* windowListHead; } ;
typedef  int /*<<< orphan*/  GLFWid ;

/* Variables and functions */
 TYPE_3__ _glfw ; 

_GLFWwindow* _glfwWindowForId(GLFWid id) {
    _GLFWwindow *w = _glfw.windowListHead;
    while (w) {
        if (w->id == _glfw.focusedWindowId) return w;
        w = w->next;
    }
    return NULL;
}