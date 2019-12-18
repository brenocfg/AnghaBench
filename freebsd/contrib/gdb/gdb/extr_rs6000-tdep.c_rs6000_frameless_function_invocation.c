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
struct rs6000_framedata {int frameless; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ SIGTRAMP_FRAME ; 
 int /*<<< orphan*/  get_frame_func (struct frame_info*) ; 
 scalar_t__ get_frame_pc (struct frame_info*) ; 
 scalar_t__ get_frame_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_next_frame (struct frame_info*) ; 
 int /*<<< orphan*/  skip_prologue (int /*<<< orphan*/ ,scalar_t__,struct rs6000_framedata*) ; 

int
rs6000_frameless_function_invocation (struct frame_info *fi)
{
  CORE_ADDR func_start;
  struct rs6000_framedata fdata;

  /* Don't even think about framelessness except on the innermost frame
     or if the function was interrupted by a signal.  */
  if (get_next_frame (fi) != NULL
      && !(get_frame_type (get_next_frame (fi)) == SIGTRAMP_FRAME))
    return 0;

  func_start = get_frame_func (fi);

  /* If we failed to find the start of the function, it is a mistake
     to inspect the instructions.  */

  if (!func_start)
    {
      /* A frame with a zero PC is usually created by dereferencing a NULL
         function pointer, normally causing an immediate core dump of the
         inferior.  Mark function as frameless, as the inferior has no chance
         of setting up a stack frame.  */
      if (get_frame_pc (fi) == 0)
	return 1;
      else
	return 0;
    }

  (void) skip_prologue (func_start, get_frame_pc (fi), &fdata);
  return fdata.frameless;
}