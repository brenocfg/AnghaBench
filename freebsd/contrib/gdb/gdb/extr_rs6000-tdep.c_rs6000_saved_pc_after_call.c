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
struct TYPE_2__ {int /*<<< orphan*/  ppc_lr_regnum; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ) ; 

__attribute__((used)) static CORE_ADDR
rs6000_saved_pc_after_call (struct frame_info *fi)
{
  return read_register (gdbarch_tdep (current_gdbarch)->ppc_lr_regnum);
}