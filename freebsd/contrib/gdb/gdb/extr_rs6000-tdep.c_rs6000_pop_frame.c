#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rs6000_framedata {scalar_t__ lr_offset; int saved_gpr; scalar_t__ gpr_offset; int saved_fpr; scalar_t__ fpr_offset; scalar_t__ frameless; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {int wordsize; int /*<<< orphan*/  ppc_lr_regnum; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DEPRECATED_PC_IN_CALL_DUMMY (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 size_t DEPRECATED_REGISTER_BYTE (int) ; 
 int /*<<< orphan*/  DEPRECATED_REGISTER_BYTES ; 
 int FP0_REGNUM ; 
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  SP_REGNUM ; 
 int /*<<< orphan*/  current_gdbarch ; 
 int /*<<< orphan*/  deprecated_read_register_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * deprecated_registers ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_pop_dummy_frame () ; 
 struct frame_info* get_current_frame () ; 
 scalar_t__ get_frame_base (struct frame_info*) ; 
 scalar_t__ get_frame_func (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  read_memory (scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ read_memory_addr (scalar_t__,int) ; 
 scalar_t__ read_pc () ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_prologue (scalar_t__,int /*<<< orphan*/ ,struct rs6000_framedata*) ; 
 int /*<<< orphan*/  target_store_registers (int) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
rs6000_pop_frame (void)
{
  CORE_ADDR pc, lr, sp, prev_sp, addr;	/* %pc, %lr, %sp */
  struct rs6000_framedata fdata;
  struct frame_info *frame = get_current_frame ();
  int ii, wordsize;

  pc = read_pc ();
  sp = get_frame_base (frame);

  if (DEPRECATED_PC_IN_CALL_DUMMY (get_frame_pc (frame),
				   get_frame_base (frame),
				   get_frame_base (frame)))
    {
      generic_pop_dummy_frame ();
      flush_cached_frames ();
      return;
    }

  /* Make sure that all registers are valid.  */
  deprecated_read_register_bytes (0, NULL, DEPRECATED_REGISTER_BYTES);

  /* Figure out previous %pc value.  If the function is frameless, it is 
     still in the link register, otherwise walk the frames and retrieve the
     saved %pc value in the previous frame.  */

  addr = get_frame_func (frame);
  (void) skip_prologue (addr, get_frame_pc (frame), &fdata);

  wordsize = gdbarch_tdep (current_gdbarch)->wordsize;
  if (fdata.frameless)
    prev_sp = sp;
  else
    prev_sp = read_memory_addr (sp, wordsize);
  if (fdata.lr_offset == 0)
     lr = read_register (gdbarch_tdep (current_gdbarch)->ppc_lr_regnum);
  else
    lr = read_memory_addr (prev_sp + fdata.lr_offset, wordsize);

  /* reset %pc value. */
  write_register (PC_REGNUM, lr);

  /* reset register values if any was saved earlier.  */

  if (fdata.saved_gpr != -1)
    {
      addr = prev_sp + fdata.gpr_offset;
      for (ii = fdata.saved_gpr; ii <= 31; ++ii)
	{
	  read_memory (addr, &deprecated_registers[DEPRECATED_REGISTER_BYTE (ii)],
		       wordsize);
	  addr += wordsize;
	}
    }

  if (fdata.saved_fpr != -1)
    {
      addr = prev_sp + fdata.fpr_offset;
      for (ii = fdata.saved_fpr; ii <= 31; ++ii)
	{
	  read_memory (addr, &deprecated_registers[DEPRECATED_REGISTER_BYTE (ii + FP0_REGNUM)], 8);
	  addr += 8;
	}
    }

  write_register (SP_REGNUM, prev_sp);
  target_store_registers (-1);
  flush_cached_frames ();
}