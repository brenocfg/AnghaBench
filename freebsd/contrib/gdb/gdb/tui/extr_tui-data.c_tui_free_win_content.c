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
typedef  int /*<<< orphan*/  tui_win_content ;
struct tui_gen_win_info {scalar_t__ content_size; int /*<<< orphan*/ * content; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_content (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
tui_free_win_content (struct tui_gen_win_info * win_info)
{
  if (win_info->content != NULL)
    {
      free_content ((tui_win_content) win_info->content,
		   win_info->content_size,
		   win_info->type);
      win_info->content = NULL;
    }
  win_info->content_size = 0;
}