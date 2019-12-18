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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSEM_COMMAND ; 
 int /*<<< orphan*/  DISASSEM_WIN ; 
 int tui_default_win_viewport_height (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_find_disassembly_address (int /*<<< orphan*/ ,int) ; 

CORE_ADDR
tui_get_low_disassembly_address (CORE_ADDR low, CORE_ADDR pc)
{
  int pos;

  /* Determine where to start the disassembly so that the pc is about in the
     middle of the viewport.  */
  pos = tui_default_win_viewport_height (DISASSEM_WIN, DISASSEM_COMMAND) / 2;
  pc = tui_find_disassembly_address (pc, -pos);

  if (pc < low)
    pc = low;
  return pc;
}