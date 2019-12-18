#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tui_gen_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  make_visible (struct tui_gen_win_info*,int /*<<< orphan*/ ) ; 

void
tui_make_invisible (struct tui_gen_win_info *win_info)
{
  make_visible (win_info, 0);
}