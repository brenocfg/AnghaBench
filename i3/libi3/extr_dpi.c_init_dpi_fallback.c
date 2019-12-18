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
struct TYPE_2__ {scalar_t__ height_in_millimeters; scalar_t__ height_in_pixels; } ;

/* Variables and functions */
 TYPE_1__* root_screen ; 

__attribute__((used)) static long init_dpi_fallback(void) {
    return (double)root_screen->height_in_pixels * 25.4 / (double)root_screen->height_in_millimeters;
}