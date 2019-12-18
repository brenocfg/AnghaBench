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

__attribute__((used)) static int instruction_is_store(unsigned int instr)
{
	unsigned int mask;

	mask = 0x10000000;
	if ((instr & 0xfc000000) == 0x7c000000)
		mask = 0x100;		/* major opcode 31 */
	return (instr & mask) != 0;
}