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
struct trad_frame_saved_reg {scalar_t__ realreg; int addr; } ;

/* Variables and functions */

int
trad_frame_realreg_p (struct trad_frame_saved_reg this_saved_regs[],
		      int regnum)
{
  return (this_saved_regs[regnum].realreg >= 0
	  && this_saved_regs[regnum].addr == -1);
}