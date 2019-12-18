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
struct gdbarch_tdep {int /*<<< orphan*/  npc_regnum; int /*<<< orphan*/  pc_regnum; } ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 scalar_t__ sparc_address_from_register (int /*<<< orphan*/ ) ; 
 scalar_t__ sparc_analyze_control_transfer (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  target_insert_breakpoint (scalar_t__,char*) ; 
 int /*<<< orphan*/  target_remove_breakpoint (scalar_t__,char*) ; 

void
sparc_software_single_step (enum target_signal sig, int insert_breakpoints_p)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  static CORE_ADDR npc, nnpc;
  static char npc_save[4], nnpc_save[4];

  if (insert_breakpoints_p)
    {
      CORE_ADDR pc;

      pc = sparc_address_from_register (tdep->pc_regnum);
      npc = sparc_address_from_register (tdep->npc_regnum);

      /* Analyze the instruction at PC.  */
      nnpc = sparc_analyze_control_transfer (pc, &npc);
      if (npc != 0)
	target_insert_breakpoint (npc, npc_save);
      if (nnpc != 0)
	target_insert_breakpoint (nnpc, nnpc_save);

      /* Assert that we have set at least one breakpoint, and that
         they're not set at the same spot.  */
      gdb_assert (npc != 0 || nnpc != 0);
      gdb_assert (nnpc != npc);
    }
  else
    {
      if (npc != 0)
	target_remove_breakpoint (npc, npc_save);
      if (nnpc != 0)
	target_remove_breakpoint (nnpc, nnpc_save);
    }
}