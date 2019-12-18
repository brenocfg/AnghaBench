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
 void* FALSE ; 
 int /*<<< orphan*/  MENU_CLOSED_Y ; 
 int /*<<< orphan*/  MENU_LAYOUT_INITIAL_X ; 
 int /*<<< orphan*/  UIMoveTo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* avatar_enabled ; 
 void* menu_enabled ; 
 scalar_t__ menu_layout ; 
 scalar_t__ text_count ; 
 char* text_lines ; 
 int text_num_lines ; 
 int /*<<< orphan*/  text_out_speed ; 
 scalar_t__ text_tile_count ; 

void UICloseDialogue()
{
  UIMoveTo(menu_layout ? MENU_LAYOUT_INITIAL_X : 0, MENU_CLOSED_Y, text_out_speed);

  // Reset variables
  text_count = 0;
  text_lines[0] = '\0';
  text_tile_count = 0;
  text_num_lines = 3;
  menu_enabled = FALSE;
  menu_layout = 0;
  avatar_enabled = FALSE;
}