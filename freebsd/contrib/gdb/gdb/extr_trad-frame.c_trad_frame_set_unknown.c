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
struct trad_frame_saved_reg {int addr; int /*<<< orphan*/  realreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_UNKNOWN ; 

void
trad_frame_set_unknown (struct trad_frame_saved_reg this_saved_regs[],
			int regnum)
{
  /* Make the REALREG invalid, indicating that the value is not known.  */
  this_saved_regs[regnum].realreg = REG_UNKNOWN;
  this_saved_regs[regnum].addr = -1;
}