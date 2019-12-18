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
struct TYPE_2__ {int x; int y; } ;
struct tui_gen_win_info {TYPE_1__ origin; } ;

/* Variables and functions */

void
set_gen_win_origin (struct tui_gen_win_info * win_info, int x, int y)
{
  win_info->origin.x = x;
  win_info->origin.y = y;
}