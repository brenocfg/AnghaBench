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
struct sparc_frame_cache {int base; scalar_t__ frameless_p; scalar_t__ struct_return_p; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  enum lval_type { ____Placeholder_lval_type } lval_type ;
typedef  scalar_t__ ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int SPARC32_NPC_REGNUM ; 
 int SPARC32_PC_REGNUM ; 
 int SPARC_I0_REGNUM ; 
 int SPARC_I7_REGNUM ; 
 int SPARC_L0_REGNUM ; 
 int SPARC_O0_REGNUM ; 
 int SPARC_O7_REGNUM ; 
 int /*<<< orphan*/  frame_register_unwind (struct frame_info*,int,int*,int*,int*,int*,void*) ; 
 scalar_t__ frame_unwind_register_unsigned (struct frame_info*,int) ; 
 struct gdbarch* get_frame_arch (struct frame_info*) ; 
 scalar_t__ get_frame_memory_unsigned (struct frame_info*,int,int) ; 
 int lval_memory ; 
 int not_lval ; 
 int /*<<< orphan*/  read_memory (int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_size (struct gdbarch*,int) ; 
 struct sparc_frame_cache* sparc32_frame_cache (struct frame_info*,void**) ; 
 scalar_t__ sparc_fetch_wcookie () ; 
 int /*<<< orphan*/  store_unsigned_integer (void*,int,scalar_t__) ; 

__attribute__((used)) static void
sparc32_frame_prev_register (struct frame_info *next_frame, void **this_cache,
			     int regnum, int *optimizedp,
			     enum lval_type *lvalp, CORE_ADDR *addrp,
			     int *realnump, void *valuep)
{
  struct sparc_frame_cache *cache =
    sparc32_frame_cache (next_frame, this_cache);

  if (regnum == SPARC32_PC_REGNUM || regnum == SPARC32_NPC_REGNUM)
    {
      *optimizedp = 0;
      *lvalp = not_lval;
      *addrp = 0;
      *realnump = -1;
      if (valuep)
	{
	  CORE_ADDR pc = (regnum == SPARC32_NPC_REGNUM) ? 4 : 0;

	  /* If this functions has a Structure, Union or
             Quad-Precision return value, we have to skip the UNIMP
             instruction that encodes the size of the structure.  */
	  if (cache->struct_return_p)
	    pc += 4;

	  regnum = cache->frameless_p ? SPARC_O7_REGNUM : SPARC_I7_REGNUM;
	  pc += frame_unwind_register_unsigned (next_frame, regnum) + 8;
	  store_unsigned_integer (valuep, 4, pc);
	}
      return;
    }

  /* Handle StackGhost.  */
  {
    ULONGEST wcookie = sparc_fetch_wcookie ();

    if (wcookie != 0 && !cache->frameless_p && regnum == SPARC_I7_REGNUM)
      {
	*optimizedp = 0;
	*lvalp = not_lval;
	*addrp = 0;
	*realnump = -1;
	if (valuep)
	  {
	    CORE_ADDR addr = cache->base + (regnum - SPARC_L0_REGNUM) * 4;
	    ULONGEST i7;

	    /* Read the value in from memory.  */
	    i7 = get_frame_memory_unsigned (next_frame, addr, 4);
	    store_unsigned_integer (valuep, 4, i7 ^ wcookie);
	  }
	return;
      }
  }

  /* The previous frame's `local' and `in' registers have been saved
     in the register save area.  */
  if (!cache->frameless_p
      && regnum >= SPARC_L0_REGNUM && regnum <= SPARC_I7_REGNUM)
    {
      *optimizedp = 0;
      *lvalp = lval_memory;
      *addrp = cache->base + (regnum - SPARC_L0_REGNUM) * 4;
      *realnump = -1;
      if (valuep)
	{
	  struct gdbarch *gdbarch = get_frame_arch (next_frame);

	  /* Read the value in from memory.  */
	  read_memory (*addrp, valuep, register_size (gdbarch, regnum));
	}
      return;
    }

  /* The previous frame's `out' registers are accessable as the
     current frame's `in' registers.  */
  if (!cache->frameless_p
      && regnum >= SPARC_O0_REGNUM && regnum <= SPARC_O7_REGNUM)
    regnum += (SPARC_I0_REGNUM - SPARC_O0_REGNUM);

  frame_register_unwind (next_frame, regnum,
			 optimizedp, lvalp, addrp, realnump, valuep);
}