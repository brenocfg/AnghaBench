#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wl_output {int dummy; } ;
struct TYPE_2__ {int scale; } ;
struct _GLFWmonitor {TYPE_1__ wl; } ;
typedef  int int32_t ;

/* Variables and functions */

__attribute__((used)) static void outputHandleScale(void* data,
                            struct wl_output* output,
                            int32_t factor)
{
    struct _GLFWmonitor *monitor = data;
    if (factor > 0 && factor < 24)
        monitor->wl.scale = factor;
}