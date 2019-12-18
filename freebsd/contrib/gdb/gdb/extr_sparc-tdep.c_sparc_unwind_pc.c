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
struct gdbarch_tdep {int /*<<< orphan*/  pc_regnum; } ;
struct gdbarch {int dummy; } ;
struct frame_info {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  frame_unwind_register_unsigned (struct frame_info*,int /*<<< orphan*/ ) ; 
 struct gdbarch_tdep* gdbarch_tdep (struct gdbarch*) ; 

__attribute__((used)) static CORE_ADDR
sparc_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);
  return frame_unwind_register_unsigned (next_frame, tdep->pc_regnum);
}