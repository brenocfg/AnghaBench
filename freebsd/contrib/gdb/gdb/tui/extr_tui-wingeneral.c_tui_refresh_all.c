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
struct tui_gen_win_info {int /*<<< orphan*/  handle; scalar_t__ is_visible; } ;
struct TYPE_3__ {struct tui_gen_win_info* execution_info; } ;
struct TYPE_4__ {TYPE_1__ source_info; } ;
struct tui_win_info {struct tui_gen_win_info generic; TYPE_2__ detail; } ;
typedef  enum tui_win_type { ____Placeholder_tui_win_type } tui_win_type ;

/* Variables and functions */
 int DISASSEM_WIN ; 
 int MAX_MAJOR_WINDOWS ; 
 int SRC_WIN ; 
 int /*<<< orphan*/  touchwin (int /*<<< orphan*/ ) ; 
 struct tui_gen_win_info* tui_locator_win_info_ptr () ; 
 int /*<<< orphan*/  tui_refresh_win (struct tui_gen_win_info*) ; 

void
tui_refresh_all (struct tui_win_info * * list)
{
  enum tui_win_type type;
  struct tui_gen_win_info * locator = tui_locator_win_info_ptr ();

  for (type = SRC_WIN; (type < MAX_MAJOR_WINDOWS); type++)
    {
      if (list[type] && list[type]->generic.is_visible)
	{
	  if (type == SRC_WIN || type == DISASSEM_WIN)
	    {
	      touchwin (list[type]->detail.source_info.execution_info->handle);
	      tui_refresh_win (list[type]->detail.source_info.execution_info);
	    }
	  touchwin (list[type]->generic.handle);
	  tui_refresh_win (&list[type]->generic);
	}
    }
  if (locator->is_visible)
    {
      touchwin (locator->handle);
      tui_refresh_win (locator);
    }
}