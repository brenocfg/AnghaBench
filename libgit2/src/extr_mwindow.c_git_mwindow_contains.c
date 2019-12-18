#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_off_t ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_5__ {scalar_t__ offset; TYPE_1__ window_map; } ;
typedef  TYPE_2__ git_mwindow ;

/* Variables and functions */

int git_mwindow_contains(git_mwindow *win, git_off_t offset)
{
	git_off_t win_off = win->offset;
	return win_off <= offset
		&& offset <= (git_off_t)(win_off + win->window_map.len);
}