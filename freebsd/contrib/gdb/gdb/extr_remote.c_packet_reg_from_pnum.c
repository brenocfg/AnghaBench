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
struct packet_reg {scalar_t__ pnum; } ;
typedef  scalar_t__ LONGEST ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 

__attribute__((used)) static struct packet_reg *
packet_reg_from_pnum (struct remote_state *rs, LONGEST pnum)
{
  int i;
  for (i = 0; i < NUM_REGS + NUM_PSEUDO_REGS; i++)
    {
      struct packet_reg *r = &rs->regs[i];
      if (r->pnum == pnum)
	return r;
    }
  return NULL;
}