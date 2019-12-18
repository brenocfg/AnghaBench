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
struct symtab_and_line {TYPE_1__* symtab; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_3__ {char* filename; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ tui_get_begin_asm_address () ; 
 TYPE_2__* tui_source_windows () ; 
 int /*<<< orphan*/  tui_update_locator_filename (char*) ; 
 int /*<<< orphan*/  tui_update_source_windows_with_addr (scalar_t__) ; 

void
tui_display_main (void)
{
  if ((tui_source_windows ())->count > 0)
    {
      CORE_ADDR addr;

      addr = tui_get_begin_asm_address ();
      if (addr != (CORE_ADDR) 0)
	{
	  struct symtab_and_line sal;

	  tui_update_source_windows_with_addr (addr);
	  sal = find_pc_line (addr, 0);
          if (sal.symtab)
             tui_update_locator_filename (sal.symtab->filename);
          else
             tui_update_locator_filename ("??");
	}
    }
}