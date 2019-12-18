#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  _GLFWwindow ;
struct TYPE_6__ {int mask_len; unsigned char* mask; int /*<<< orphan*/  deviceid; } ;
typedef  TYPE_2__ XIEventMask ;
struct TYPE_5__ {int /*<<< orphan*/  root; int /*<<< orphan*/  display; } ;
struct TYPE_7__ {TYPE_1__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XIAllMasterDevices ; 
 int /*<<< orphan*/  XISelectEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_3__ _glfw ; 

__attribute__((used)) static void disableRawMouseMotion(_GLFWwindow* window)
{
    XIEventMask em;
    unsigned char mask[] = { 0 };

    em.deviceid = XIAllMasterDevices;
    em.mask_len = sizeof(mask);
    em.mask = mask;

    XISelectEvents(_glfw.x11.display, _glfw.x11.root, &em, 1);
}