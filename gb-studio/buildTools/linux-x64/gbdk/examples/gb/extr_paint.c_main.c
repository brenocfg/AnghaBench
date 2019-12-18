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
 int /*<<< orphan*/  BLACK ; 
 int OBP1_REG ; 
 int /*<<< orphan*/  PEN ; 
 int /*<<< orphan*/  SOLID ; 
 int /*<<< orphan*/  current_color ; 
 int /*<<< orphan*/  current_cursor ; 
 int /*<<< orphan*/  current_mode ; 
 scalar_t__ current_tool ; 
 int cursor_x ; 
 int cursor_y ; 
 scalar_t__ menu_cursor_pos ; 
 int /*<<< orphan*/  run () ; 
 int /*<<< orphan*/  splash () ; 

void main()
{
  /* Initialize sprite palette */
  OBP1_REG = 0xE0U;

  splash();

  current_tool = 0;
  current_color = BLACK;
  current_mode = SOLID;
  current_cursor = PEN;
  menu_cursor_pos = 0;
  cursor_x = 160/2;
  cursor_y = 144/2;

  run();
}