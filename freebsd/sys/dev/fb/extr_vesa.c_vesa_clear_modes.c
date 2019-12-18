#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ vi_mode; int vi_flags; } ;
typedef  TYPE_1__ video_info_t ;

/* Variables and functions */
 scalar_t__ EOT ; 
 scalar_t__ NA ; 
 int V_INFO_COLOR ; 

__attribute__((used)) static void
vesa_clear_modes(video_info_t *info, int color)
{
	while (info->vi_mode != EOT) {
		if ((info->vi_flags & V_INFO_COLOR) != color)
			info->vi_mode = NA;
		++info;
	}
}