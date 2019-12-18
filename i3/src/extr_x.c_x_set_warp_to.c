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
struct TYPE_2__ {scalar_t__ mouse_warping; } ;
typedef  int /*<<< orphan*/  Rect ;

/* Variables and functions */
 scalar_t__ POINTER_WARPING_NONE ; 
 TYPE_1__ config ; 
 int /*<<< orphan*/ * warp_to ; 

void x_set_warp_to(Rect *rect) {
    if (config.mouse_warping != POINTER_WARPING_NONE)
        warp_to = rect;
}