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
struct TYPE_3__ {scalar_t__ has_locator; } ;
struct TYPE_4__ {TYPE_1__ source_info; } ;
struct tui_win_info {TYPE_2__ detail; } ;

/* Variables and functions */

int
tui_win_has_locator (struct tui_win_info *win_info)
{
  return (win_info != NULL \
	  && win_info->detail.source_info.has_locator);
}