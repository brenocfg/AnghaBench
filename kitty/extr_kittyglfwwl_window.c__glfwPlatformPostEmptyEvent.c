#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * wakeupFds; } ;
struct TYPE_5__ {TYPE_1__ eventLoopData; } ;
struct TYPE_6__ {TYPE_2__ wl; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 TYPE_3__ _glfw ; 
 scalar_t__ errno ; 
 scalar_t__ write (int /*<<< orphan*/ ,char*,int) ; 

void _glfwPlatformPostEmptyEvent(void)
{
    while (write(_glfw.wl.eventLoopData.wakeupFds[1], "w", 1) < 0 && errno == EINTR);
}