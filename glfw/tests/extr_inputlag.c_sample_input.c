#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float x; float y; } ;
struct TYPE_4__ {float x; float y; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 scalar_t__ cursor_method ; 
 TYPE_2__ cursor_new ; 
 TYPE_2__ cursor_pos ; 
 scalar_t__ cursor_sync_query ; 
 TYPE_1__ cursor_vel ; 
 int /*<<< orphan*/  glfwGetCursorPos (int /*<<< orphan*/ *,double*,double*) ; 

void sample_input(GLFWwindow* window)
{
    float a = .25; // exponential smoothing factor

    if (cursor_method == cursor_sync_query) {
        double x, y;
        glfwGetCursorPos(window, &x, &y);
        cursor_new.x = (float) x;
        cursor_new.y = (float) y;
    }

    cursor_vel.x = (cursor_new.x - cursor_pos.x) * a + cursor_vel.x * (1 - a);
    cursor_vel.y = (cursor_new.y - cursor_pos.y) * a + cursor_vel.y * (1 - a);
    cursor_pos = cursor_new;
}