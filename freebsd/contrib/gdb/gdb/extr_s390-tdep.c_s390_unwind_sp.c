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
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  S390_SP_REGNUM ; 
 int /*<<< orphan*/  frame_unwind_register_unsigned (struct frame_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_addr_bits_remove (struct gdbarch*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
s390_unwind_sp (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  ULONGEST sp;
  sp = frame_unwind_register_unsigned (next_frame, S390_SP_REGNUM);
  return gdbarch_addr_bits_remove (gdbarch, sp);
}