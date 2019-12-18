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
struct frame_unwind {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int S390_MAX_INSTR_SIZE ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 scalar_t__ in_plt_section (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ s390_readinstruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct frame_unwind const s390_stub_frame_unwind ; 

__attribute__((used)) static const struct frame_unwind *
s390_stub_frame_sniffer (struct frame_info *next_frame)
{
  CORE_ADDR pc = frame_pc_unwind (next_frame);
  bfd_byte insn[S390_MAX_INSTR_SIZE];

  /* If the current PC points to non-readable memory, we assume we
     have trapped due to an invalid function pointer call.  We handle
     the non-existing current function like a PLT stub.  */
  if (in_plt_section (pc, NULL)
      || s390_readinstruction (insn, pc) < 0)
    return &s390_stub_frame_unwind;
  return NULL;
}