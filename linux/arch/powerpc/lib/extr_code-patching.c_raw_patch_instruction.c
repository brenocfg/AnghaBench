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

/* Variables and functions */
 int __patch_instruction (unsigned int*,unsigned int,unsigned int*) ; 

int raw_patch_instruction(unsigned int *addr, unsigned int instr)
{
	return __patch_instruction(addr, instr, addr);
}