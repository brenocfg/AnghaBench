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
struct trad_frame_saved_reg {scalar_t__ addr; int /*<<< orphan*/  realreg; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_register_unwind (struct frame_info*,int /*<<< orphan*/ ,int*,int*,scalar_t__*,int*,void*) ; 
 int /*<<< orphan*/  gdbarch_register_name (struct gdbarch*,int) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_memory (struct frame_info*,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int lval_memory ; 
 int not_lval ; 
 int /*<<< orphan*/  register_size (struct gdbarch*,int) ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ trad_frame_addr_p (struct trad_frame_saved_reg*,int) ; 
 scalar_t__ trad_frame_realreg_p (struct trad_frame_saved_reg*,int) ; 
 scalar_t__ trad_frame_value_p (struct trad_frame_saved_reg*,int) ; 

void
trad_frame_prev_register (struct frame_info *next_frame,
			  struct trad_frame_saved_reg this_saved_regs[],
			  int regnum, int *optimizedp,
			  enum lval_type *lvalp, CORE_ADDR *addrp,
			  int *realregp, void *bufferp)
{
  struct gdbarch *gdbarch = get_frame_arch (next_frame);
  if (trad_frame_addr_p (this_saved_regs, regnum))
    {
      /* The register was saved in memory.  */
      *optimizedp = 0;
      *lvalp = lval_memory;
      *addrp = this_saved_regs[regnum].addr;
      *realregp = -1;
      if (bufferp != NULL)
	{
	  /* Read the value in from memory.  */
	  get_frame_memory (next_frame, this_saved_regs[regnum].addr, bufferp,
			    register_size (gdbarch, regnum));
	}
    }
  else if (trad_frame_realreg_p (this_saved_regs, regnum))
    {
      /* Ask the next frame to return the value of the register.  */
      frame_register_unwind (next_frame, this_saved_regs[regnum].realreg,
			     optimizedp, lvalp, addrp, realregp, bufferp);
    }
  else if (trad_frame_value_p (this_saved_regs, regnum))
    {
      /* The register's value is available.  */
      *optimizedp = 0;
      *lvalp = not_lval;
      *addrp = 0;
      *realregp = -1;
      if (bufferp != NULL)
	store_unsigned_integer (bufferp, register_size (gdbarch, regnum),
				this_saved_regs[regnum].addr);
    }
  else
    {
      error ("Register %s not available",
	     gdbarch_register_name (gdbarch, regnum));
    }
}