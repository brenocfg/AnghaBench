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
struct frame_info {int dummy; } ;
struct TYPE_2__ {int wordsize; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ DEPRECATED_FRAMELESS_FUNCTION_INVOCATION (struct frame_info*) ; 
 scalar_t__ DEPRECATED_FRAMELESS_FUNCTION_INVOCATION_P () ; 
 scalar_t__ DEPRECATED_PC_IN_CALL_DUMMY (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ SIGTRAMP_FRAME ; 
 scalar_t__ SIG_FRAME_FP_OFFSET ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ deprecated_inside_entry_file (scalar_t__) ; 
 scalar_t__ entry_point_address () ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 scalar_t__ get_frame_base (struct frame_info*) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 scalar_t__ get_frame_type (struct frame_info*) ; 
 struct frame_info* get_next_frame (struct frame_info*) ; 
 scalar_t__ read_memory_addr (scalar_t__,int) ; 

CORE_ADDR
rs6000_frame_chain (struct frame_info *thisframe)
{
  CORE_ADDR fp, fpp, lr;
  int wordsize = gdbarch_tdep (current_gdbarch)->wordsize;

  if (DEPRECATED_PC_IN_CALL_DUMMY (get_frame_pc (thisframe),
				   get_frame_base (thisframe),
				   get_frame_base (thisframe)))
    /* A dummy frame always correctly chains back to the previous
       frame.  */
    return read_memory_addr (get_frame_base (thisframe), wordsize);

  if (deprecated_inside_entry_file (get_frame_pc (thisframe))
      || get_frame_pc (thisframe) == entry_point_address ())
    return 0;

  if ((get_frame_type (thisframe) == SIGTRAMP_FRAME))
    fp = read_memory_addr (get_frame_base (thisframe) + SIG_FRAME_FP_OFFSET,
			   wordsize);
  else if (get_next_frame (thisframe) != NULL
	   && (get_frame_type (get_next_frame (thisframe)) == SIGTRAMP_FRAME)
	   && (DEPRECATED_FRAMELESS_FUNCTION_INVOCATION_P ()
	       && DEPRECATED_FRAMELESS_FUNCTION_INVOCATION (thisframe)))
    /* A frameless function interrupted by a signal did not change the
       frame pointer.  */
    fp = get_frame_base (thisframe);
  else
    fp = read_memory_addr (get_frame_base (thisframe), wordsize);
  return fp;
}