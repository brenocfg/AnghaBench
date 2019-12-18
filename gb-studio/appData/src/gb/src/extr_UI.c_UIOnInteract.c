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

/* Variables and functions */
 scalar_t__ JOY_PRESSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  J_A ; 
 int /*<<< orphan*/  J_B ; 
 int /*<<< orphan*/  J_DOWN ; 
 int /*<<< orphan*/  J_LEFT ; 
 int /*<<< orphan*/  J_RIGHT ; 
 int /*<<< orphan*/  J_UP ; 
 scalar_t__ MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  UICloseDialogue () ; 
 int /*<<< orphan*/  UIDrawMenuCursor () ; 
 scalar_t__ menu_cancel_on_b ; 
 scalar_t__ menu_cancel_on_last_option ; 
 scalar_t__ menu_enabled ; 
 size_t menu_flag ; 
 scalar_t__ menu_index ; 
 scalar_t__ menu_layout ; 
 scalar_t__ menu_num_options ; 
 scalar_t__* script_variables ; 
 scalar_t__ text_count ; 
 scalar_t__ text_drawn ; 

void UIOnInteract()
{
  if (JOY_PRESSED(J_A))
  {
    if (text_drawn && text_count != 0)
    {
      if (menu_enabled)
      {
        if (menu_cancel_on_last_option && menu_index + 1 == menu_num_options) 
        {
          script_variables[menu_flag] = 0;
        }
        else
        {
          script_variables[menu_flag] = menu_index + 1;
        }
        UICloseDialogue();
      }
      else
      {
        UICloseDialogue();
      }
    }
  }
  else if (menu_enabled)
  {
    if (JOY_PRESSED(J_UP))
    {
      menu_index = MAX(menu_index - 1, 0);
      UIDrawMenuCursor();
    }
    else if (JOY_PRESSED(J_DOWN))
    {
      menu_index = MIN(menu_index + 1, menu_num_options - 1);
      UIDrawMenuCursor();
    }
    else if (JOY_PRESSED(J_LEFT))
    {
      if(menu_layout == 0) {
        menu_index = MAX(menu_index - 4, 0);
      } else {
        menu_index = 0;
      }      
      UIDrawMenuCursor();
    }
    else if (JOY_PRESSED(J_RIGHT))
    {
      if(menu_layout == 0) {
        menu_index = MIN(menu_index + 4, menu_num_options - 1);
      } else {
        menu_index = menu_num_options - 1;
      }
      UIDrawMenuCursor();
    }
    else if (menu_cancel_on_b && JOY_PRESSED(J_B))
    {
      script_variables[menu_flag] = 0;
      UICloseDialogue();
    }
  }
}