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
struct TYPE_3__ {int width; int height; } ;
struct TYPE_4__ {TYPE_1__ generic; } ;

/* Variables and functions */
 TYPE_2__* TUI_CMD_WIN ; 
 int /*<<< orphan*/  tui_active ; 

int
tui_get_command_dimension (int *width, int *height)
{
  if (!tui_active || (TUI_CMD_WIN == NULL))
    {
      return 0;
    }
  
  *width = TUI_CMD_WIN->generic.width;
  *height = TUI_CMD_WIN->generic.height;
  return 1;
}