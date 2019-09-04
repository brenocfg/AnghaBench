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
struct TYPE_3__ {unsigned int xnum; unsigned int ynum; unsigned int z; } ;
struct TYPE_4__ {TYPE_1__ sprite_tracker; } ;
typedef  TYPE_2__ FontGroup ;
typedef  scalar_t__ FONTS_DATA_HANDLE ;

/* Variables and functions */

void
sprite_tracker_current_layout(FONTS_DATA_HANDLE data, unsigned int *x, unsigned int *y, unsigned int *z) {
    FontGroup *fg = (FontGroup*)data;
    *x = fg->sprite_tracker.xnum; *y = fg->sprite_tracker.ynum; *z = fg->sprite_tracker.z;
}