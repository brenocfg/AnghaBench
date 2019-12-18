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
struct tui_win_info {int dummy; } ;
struct TYPE_2__ {int count; void** list; } ;

/* Variables and functions */
 TYPE_1__ source_windows ; 

void
tui_add_to_source_windows (struct tui_win_info * win_info)
{
  if (source_windows.count < 2)
    source_windows.list[source_windows.count++] = (void *) win_info;
}