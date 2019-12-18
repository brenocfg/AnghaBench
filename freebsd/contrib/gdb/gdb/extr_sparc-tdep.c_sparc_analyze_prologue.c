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
struct sparc_frame_cache {scalar_t__ frameless_p; } ;
struct gdbarch_tdep {scalar_t__ plt_entry_size; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ X_I (unsigned long) ; 
 int X_OP (unsigned long) ; 
 int X_OP2 (unsigned long) ; 
 int X_OP3 (unsigned long) ; 
 int X_RD (unsigned long) ; 
 int /*<<< orphan*/  current_gdbarch ; 
 struct gdbarch_tdep* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 scalar_t__ in_plt_section (scalar_t__,int /*<<< orphan*/ *) ; 
 unsigned long sparc_fetch_instruction (scalar_t__) ; 

CORE_ADDR
sparc_analyze_prologue (CORE_ADDR pc, CORE_ADDR current_pc,
			struct sparc_frame_cache *cache)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (current_gdbarch);
  unsigned long insn;
  int offset = 0;
  int dest = -1;

  if (current_pc <= pc)
    return current_pc;

  /* We have to handle to "Procedure Linkage Table" (PLT) special.  On
     SPARC the linker usually defines a symbol (typically
     _PROCEDURE_LINKAGE_TABLE_) at the start of the .plt section.
     This symbol makes us end up here with PC pointing at the start of
     the PLT and CURRENT_PC probably pointing at a PLT entry.  If we
     would do our normal prologue analysis, we would probably conclude
     that we've got a frame when in reality we don't, since the
     dynamic linker patches up the first PLT with some code that
     starts with a SAVE instruction.  Patch up PC such that it points
     at the start of our PLT entry.  */
  if (tdep->plt_entry_size > 0 && in_plt_section (current_pc, NULL))
    pc = current_pc - ((current_pc - pc) % tdep->plt_entry_size);

  insn = sparc_fetch_instruction (pc);

  /* Recognize a SETHI insn and record its destination.  */
  if (X_OP (insn) == 0 && X_OP2 (insn) == 0x04)
    {
      dest = X_RD (insn);
      offset += 4;

      insn = sparc_fetch_instruction (pc + 4);
    }

  /* Allow for an arithmetic operation on DEST or %g1.  */
  if (X_OP (insn) == 2 && X_I (insn)
      && (X_RD (insn) == 1 || X_RD (insn) == dest))
    {
      offset += 4;

      insn = sparc_fetch_instruction (pc + 8);
    }

  /* Check for the SAVE instruction that sets up the frame.  */
  if (X_OP (insn) == 2 && X_OP3 (insn) == 0x3c)
    {
      cache->frameless_p = 0;
      return pc + offset + 4;
    }

  return pc;
}