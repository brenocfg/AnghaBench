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
typedef  int /*<<< orphan*/  ptid_t ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register_pid (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sparc_write_pc (CORE_ADDR pc, ptid_t ptid)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);

  write_register_pid (tdep->pc_regnum, pc, ptid);
  write_register_pid (tdep->npc_regnum, pc + 4, ptid);
}