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
struct s390_unwind_cache {scalar_t__ func; scalar_t__ local_base; scalar_t__ frame_base; TYPE_1__* saved_regs; } ;
struct s390_prologue_data {int gpr_size; scalar_t__ fpr_size; struct prologue_value* spill; struct prologue_value* gpr; } ;
struct prologue_value {scalar_t__ kind; size_t reg; scalar_t__ k; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  data ;
typedef  scalar_t__ ULONGEST ;
struct TYPE_2__ {size_t realreg; scalar_t__ addr; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ NORMAL_FRAME ; 
 int S390_FRAME_REGNUM ; 
 int S390_NUM_SPILL_SLOTS ; 
 size_t S390_PC_REGNUM ; 
 size_t S390_R0_REGNUM ; 
 size_t S390_RETADDR_REGNUM ; 
 size_t S390_SP_REGNUM ; 
 scalar_t__ frame_func_unwind (struct frame_info*) ; 
 scalar_t__ frame_pc_unwind (struct frame_info*) ; 
 scalar_t__ frame_relative_level (struct frame_info*) ; 
 scalar_t__ frame_unwind_register_unsigned (struct frame_info*,int) ; 
 scalar_t__ gdbarch_addr_bits_remove (struct gdbarch*,scalar_t__) ; 
 int gdbarch_ptr_bit (struct gdbarch*) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 scalar_t__ get_pc_function_start (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct s390_prologue_data*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pv_is_identical (struct prologue_value*,struct prologue_value*) ; 
 scalar_t__ pv_register ; 
 scalar_t__ s390_analyze_prologue (struct gdbarch*,scalar_t__,scalar_t__,struct s390_prologue_data*) ; 
 scalar_t__ s390_in_function_epilogue_p (struct gdbarch*,scalar_t__) ; 
 int /*<<< orphan*/  trad_frame_addr_p (TYPE_1__*,size_t) ; 

__attribute__((used)) static int
s390_prologue_frame_unwind_cache (struct frame_info *next_frame,
				  struct s390_unwind_cache *info)
{
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  int word_size = gdbarch_ptr_bit (gdbarch) / 8;
  struct s390_prologue_data data;
  struct prologue_value *fp = &data.gpr[S390_FRAME_REGNUM - S390_R0_REGNUM];
  struct prologue_value *sp = &data.gpr[S390_SP_REGNUM - S390_R0_REGNUM];
  int slot_num;
  CORE_ADDR slot_addr;
  CORE_ADDR func;
  CORE_ADDR result;
  ULONGEST reg;
  CORE_ADDR prev_sp;
  int frame_pointer;
  int size;

  /* Try to find the function start address.  If we can't find it, we don't
     bother searching for it -- with modern compilers this would be mostly
     pointless anyway.  Trust that we'll either have valid DWARF-2 CFI data
     or else a valid backchain ...  */
  func = frame_func_unwind (next_frame);
  if (!func)
    return 0;

  /* Try to analyze the prologue.  */
  result = s390_analyze_prologue (gdbarch, func,
				  frame_pc_unwind (next_frame), &data);
  if (!result)
    return 0;

  /* If this was successful, we should have found the instruction that
     sets the stack pointer register to the previous value of the stack 
     pointer minus the frame size.  */
  if (sp->kind != pv_register || sp->reg != S390_SP_REGNUM)
    return 0;

  /* A frame size of zero at this point can mean either a real 
     frameless function, or else a failure to find the prologue.
     Perform some sanity checks to verify we really have a 
     frameless function.  */
  if (sp->k == 0)
    {
      /* If the next frame is a NORMAL_FRAME, this frame *cannot* have frame 
	 size zero.  This is only possible if the next frame is a sentinel 
	 frame, a dummy frame, or a signal trampoline frame.  */
      if (get_frame_type (next_frame) == NORMAL_FRAME
	  /* For some reason, sentinel frames are NORMAL_FRAMEs
	     -- but they have negative frame level.  */
	  && frame_relative_level (next_frame) >= 0)
	return 0;

      /* If we really have a frameless function, %r14 must be valid
	 -- in particular, it must point to a different function.  */
      reg = frame_unwind_register_unsigned (next_frame, S390_RETADDR_REGNUM);
      reg = gdbarch_addr_bits_remove (gdbarch, reg) - 1;
      if (get_pc_function_start (reg) == func)
	{
	  /* However, there is one case where it *is* valid for %r14
	     to point to the same function -- if this is a recursive
	     call, and we have stopped in the prologue *before* the
	     stack frame was allocated.

	     Recognize this case by looking ahead a bit ...  */

	  struct s390_prologue_data data2;
	  struct prologue_value *sp = &data2.gpr[S390_SP_REGNUM - S390_R0_REGNUM];

	  if (!(s390_analyze_prologue (gdbarch, func, (CORE_ADDR)-1, &data2)
	        && sp->kind == pv_register
	        && sp->reg == S390_SP_REGNUM
	        && sp->k != 0))
	    return 0;
	}
    }


  /* OK, we've found valid prologue data.  */
  size = -sp->k;

  /* If the frame pointer originally also holds the same value
     as the stack pointer, we're probably using it.  If it holds
     some other value -- even a constant offset -- it is most
     likely used as temp register.  */
  if (pv_is_identical (sp, fp))
    frame_pointer = S390_FRAME_REGNUM;
  else
    frame_pointer = S390_SP_REGNUM;

  /* If we've detected a function with stack frame, we'll still have to 
     treat it as frameless if we're currently within the function epilog 
     code at a point where the frame pointer has already been restored.  
     This can only happen in an innermost frame.  */
  if (size > 0
      && (get_frame_type (next_frame) != NORMAL_FRAME
	  || frame_relative_level (next_frame) < 0))
    {
      /* See the comment in s390_in_function_epilogue_p on why this is
	 not completely reliable ...  */
      if (s390_in_function_epilogue_p (gdbarch, frame_pc_unwind (next_frame)))
	{
	  memset (&data, 0, sizeof (data));
	  size = 0;
	  frame_pointer = S390_SP_REGNUM;
	}
    }

  /* Once we know the frame register and the frame size, we can unwind
     the current value of the frame register from the next frame, and
     add back the frame size to arrive that the previous frame's 
     stack pointer value.  */
  prev_sp = frame_unwind_register_unsigned (next_frame, frame_pointer) + size;

  /* Scan the spill array; if a spill slot says it holds the
     original value of some register, then record that slot's
     address as the place that register was saved.  */

  /* Slots for %r2 .. %r15.  */
  for (slot_num = 0, slot_addr = prev_sp + 2 * data.gpr_size;
       slot_num < 14;
       slot_num++, slot_addr += data.gpr_size)
    {
      struct prologue_value *slot = &data.spill[slot_num];

      if (slot->kind == pv_register
          && slot->k == 0)
        info->saved_regs[slot->reg].addr = slot_addr;
    }

  /* Slots for %f0 .. %f6.  */
  for (slot_num = 14, slot_addr = prev_sp + 16 * data.gpr_size;
       slot_num < S390_NUM_SPILL_SLOTS;
       slot_num++, slot_addr += data.fpr_size)
    {
      struct prologue_value *slot = &data.spill[slot_num];

      if (slot->kind == pv_register
          && slot->k == 0)
        info->saved_regs[slot->reg].addr = slot_addr;
    }

  /* Function return will set PC to %r14.  */
  info->saved_regs[S390_PC_REGNUM] = info->saved_regs[S390_RETADDR_REGNUM];

  /* In frameless functions, we unwind simply by moving the return
     address to the PC.  However, if we actually stored to the
     save area, use that -- we might only think the function frameless
     because we're in the middle of the prologue ...  */
  if (size == 0
      && !trad_frame_addr_p (info->saved_regs, S390_PC_REGNUM))
    {
      info->saved_regs[S390_PC_REGNUM].realreg = S390_RETADDR_REGNUM;
    }

  /* Another sanity check: unless this is a frameless function,
     we should have found spill slots for SP and PC.
     If not, we cannot unwind further -- this happens e.g. in
     libc's thread_start routine.  */
  if (size > 0)
    {
      if (!trad_frame_addr_p (info->saved_regs, S390_SP_REGNUM)
	  || !trad_frame_addr_p (info->saved_regs, S390_PC_REGNUM))
	prev_sp = -1;
    }

  /* We use the current value of the frame register as local_base,
     and the top of the register save area as frame_base.  */
  if (prev_sp != -1)
    {
      info->frame_base = prev_sp + 16*word_size + 32;
      info->local_base = prev_sp - size;
    }

  info->func = func;
  return 1;
}