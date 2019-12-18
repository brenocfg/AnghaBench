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
typedef  int uint32_t ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 scalar_t__ ldb_asm (int,int*) ; 
 int /*<<< orphan*/  put_ptreg (struct pt_regs*,int,int) ; 

__attribute__((used)) static int ldw_c(struct pt_regs *regs, uint32_t rz, uint32_t addr)
{
	uint32_t byte0, byte1, byte2, byte3;

	if (ldb_asm(addr, &byte0))
		return 1;

	addr += 1;
	if (ldb_asm(addr, &byte1))
		return 1;

	addr += 1;
	if (ldb_asm(addr, &byte2))
		return 1;

	addr += 1;
	if (ldb_asm(addr, &byte3))
		return 1;

	byte0 |= byte1 << 8;
	byte0 |= byte2 << 16;
	byte0 |= byte3 << 24;

	put_ptreg(regs, rz, byte0);

	return 0;
}