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
 int /*<<< orphan*/  tui_init_generic_part (struct tui_gen_win_info*) ; 
 scalar_t__ xmalloc (int) ; 

struct tui_gen_win_info *
tui_alloc_generic_win_info (void)
{
  struct tui_gen_win_info * win;

  if ((win = (struct tui_gen_win_info *) xmalloc (
		     sizeof (struct tui_gen_win_info *))) != (struct tui_gen_win_info *) NULL)
    tui_init_generic_part (win);

  return win;
}