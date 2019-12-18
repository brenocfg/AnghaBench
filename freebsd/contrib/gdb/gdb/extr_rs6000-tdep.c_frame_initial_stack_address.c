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
struct rs6000_framedata {scalar_t__ alloca_reg; } ;
struct frame_info {int dummy; } ;
struct TYPE_2__ {void* initial_sp; } ;
typedef  void* CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_REGISTER_RAW_SIZE (scalar_t__) ; 
 int MAX_REGISTER_SIZE ; 
 int /*<<< orphan*/  deprecated_get_frame_saved_regs (struct frame_info*) ; 
 void* extract_unsigned_integer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_get_saved_regs (struct frame_info*,struct rs6000_framedata*) ; 
 scalar_t__ frame_register_read (struct frame_info*,scalar_t__,char*) ; 
 void* get_frame_base (struct frame_info*) ; 
 TYPE_1__* get_frame_extra_info (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_func (struct frame_info*) ; 
 int /*<<< orphan*/  get_frame_pc (struct frame_info*) ; 
 int /*<<< orphan*/  skip_prologue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rs6000_framedata*) ; 

__attribute__((used)) static CORE_ADDR
frame_initial_stack_address (struct frame_info *fi)
{
  CORE_ADDR tmpaddr;
  struct rs6000_framedata fdata;
  struct frame_info *callee_fi;

  /* If the initial stack pointer (frame address) of this frame is known,
     just return it.  */

  if (get_frame_extra_info (fi)->initial_sp)
    return get_frame_extra_info (fi)->initial_sp;

  /* Find out if this function is using an alloca register.  */

  (void) skip_prologue (get_frame_func (fi), get_frame_pc (fi), &fdata);

  /* If saved registers of this frame are not known yet, read and
     cache them.  */

  if (!deprecated_get_frame_saved_regs (fi))
    frame_get_saved_regs (fi, &fdata);

  /* If no alloca register used, then fi->frame is the value of the %sp for
     this frame, and it is good enough.  */

  if (fdata.alloca_reg < 0)
    {
      get_frame_extra_info (fi)->initial_sp = get_frame_base (fi);
      return get_frame_extra_info (fi)->initial_sp;
    }

  /* There is an alloca register, use its value, in the current frame,
     as the initial stack pointer.  */
  {
    char tmpbuf[MAX_REGISTER_SIZE];
    if (frame_register_read (fi, fdata.alloca_reg, tmpbuf))
      {
	get_frame_extra_info (fi)->initial_sp
	  = extract_unsigned_integer (tmpbuf,
				      DEPRECATED_REGISTER_RAW_SIZE (fdata.alloca_reg));
      }
    else
      /* NOTE: cagney/2002-04-17: At present the only time
         frame_register_read will fail is when the register isn't
         available.  If that does happen, use the frame.  */
      get_frame_extra_info (fi)->initial_sp = get_frame_base (fi);
  }
  return get_frame_extra_info (fi)->initial_sp;
}