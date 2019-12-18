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
struct frame_id {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct frame_id frame_id_build (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frame_pc_unwind (struct frame_info*) ; 
 int gdbarch_ptr_bit (struct gdbarch*) ; 
 scalar_t__ read_memory_unsigned_integer (scalar_t__,int) ; 
 scalar_t__ s390_unwind_sp (struct gdbarch*,struct frame_info*) ; 

__attribute__((used)) static struct frame_id
s390_unwind_dummy_id (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  int word_size = gdbarch_ptr_bit (gdbarch) / 8;
  CORE_ADDR this_sp = s390_unwind_sp (gdbarch, next_frame);
  CORE_ADDR prev_sp = read_memory_unsigned_integer (this_sp, word_size);

  return frame_id_build (prev_sp + 16*word_size + 32,
                         frame_pc_unwind (next_frame));
}