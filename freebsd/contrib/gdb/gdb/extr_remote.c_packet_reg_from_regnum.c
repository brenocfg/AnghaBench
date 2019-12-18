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
struct remote_state {struct packet_reg* regs; } ;
struct packet_reg {long regnum; } ;

/* Variables and functions */
 long NUM_PSEUDO_REGS ; 
 long NUM_REGS ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static struct packet_reg *
packet_reg_from_regnum (struct remote_state *rs, long regnum)
{
  if (regnum < 0 && regnum >= NUM_REGS + NUM_PSEUDO_REGS)
    return NULL;
  else
    {
      struct packet_reg *r = &rs->regs[regnum];
      gdb_assert (r->regnum == regnum);
      return r;
    }
}