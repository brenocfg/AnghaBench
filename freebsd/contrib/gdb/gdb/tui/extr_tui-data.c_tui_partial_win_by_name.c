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
struct tui_win_info {int /*<<< orphan*/  generic; } ;

/* Variables and functions */
 int MAX_MAJOR_WINDOWS ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,scalar_t__) ; 
 struct tui_win_info** tui_win_list ; 
 char* tui_win_name (int /*<<< orphan*/ *) ; 

struct tui_win_info *
tui_partial_win_by_name (char *name)
{
  struct tui_win_info * win_info = (struct tui_win_info *) NULL;

  if (name != (char *) NULL)
    {
      int i = 0;

      while (i < MAX_MAJOR_WINDOWS && win_info == NULL)
	{
          if (tui_win_list[i] != 0)
            {
              char *cur_name = tui_win_name (&tui_win_list[i]->generic);
              if (strlen (name) <= strlen (cur_name) &&
                  strncmp (name, cur_name, strlen (name)) == 0)
                win_info = tui_win_list[i];
            }
	  i++;
	}
    }

  return win_info;
}