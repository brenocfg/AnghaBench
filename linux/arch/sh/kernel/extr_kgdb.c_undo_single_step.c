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
 int /*<<< orphan*/  __raw_writew (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  flush_icache_range (scalar_t__,scalar_t__) ; 
 scalar_t__ stepped_address ; 
 scalar_t__ stepped_opcode ; 

__attribute__((used)) static void undo_single_step(struct pt_regs *linux_regs)
{
	/* If we have stepped, put back the old instruction */
	/* Use stepped_address in case we stopped elsewhere */
	if (stepped_opcode != 0) {
		__raw_writew(stepped_opcode, stepped_address);
		flush_icache_range(stepped_address, stepped_address + 2);
	}

	stepped_opcode = 0;
}