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
struct tui_win_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSEM_WIN ; 
 int /*<<< orphan*/  make_source_or_disasm_window (struct tui_win_info**,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
make_disasm_window (struct tui_win_info * * win_info_ptr, int height, int origin_y)
{
  make_source_or_disasm_window (win_info_ptr, DISASSEM_WIN, height, origin_y);

  return;
}