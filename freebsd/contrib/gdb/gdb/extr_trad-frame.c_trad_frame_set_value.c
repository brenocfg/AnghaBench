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
struct trad_frame_saved_reg {int /*<<< orphan*/  addr; int /*<<< orphan*/  realreg; } ;
typedef  int /*<<< orphan*/  LONGEST ;

/* Variables and functions */
 int /*<<< orphan*/  REG_VALUE ; 

void
trad_frame_set_value (struct trad_frame_saved_reg this_saved_regs[],
		      int regnum, LONGEST val)
{
  /* Make the REALREG invalid, indicating that the ADDR contains the
     register's value.  */
  this_saved_regs[regnum].realreg = REG_VALUE;
  this_saved_regs[regnum].addr = val;
}