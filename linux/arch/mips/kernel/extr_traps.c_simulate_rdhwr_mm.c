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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 unsigned int MM_POOL32A_FUNC ; 
 unsigned int MM_RDHWR ; 
 unsigned int MM_RS ; 
 unsigned int MM_RT ; 
 int /*<<< orphan*/  simulate_rdhwr (struct pt_regs*,int,int) ; 

__attribute__((used)) static int simulate_rdhwr_mm(struct pt_regs *regs, unsigned int opcode)
{
	if ((opcode & MM_POOL32A_FUNC) == MM_RDHWR) {
		int rd = (opcode & MM_RS) >> 16;
		int rt = (opcode & MM_RT) >> 21;
		simulate_rdhwr(regs, rd, rt);
		return 0;
	}

	/* Not ours.  */
	return -1;
}