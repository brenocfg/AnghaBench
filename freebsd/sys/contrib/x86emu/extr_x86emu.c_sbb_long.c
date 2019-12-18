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
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_AF ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (int) ; 
 int XOR2 (int) ; 

__attribute__((used)) static uint32_t 
sbb_long(struct x86emu *emu, uint32_t d, uint32_t s)
{
	uint32_t res;	/* all operands in native machine order */
	uint32_t bc;

	if (ACCESS_FLAG(F_CF))
		res = d - s - 1;
	else
		res = d - s;
	CONDITIONAL_SET_FLAG(res & 0x80000000, F_SF);
	CONDITIONAL_SET_FLAG((res & 0xffffffff) == 0, F_ZF);
	CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);

	/* calculate the borrow chain.  See note at top */
	bc = (res & (~d | s)) | (~d & s);
	CONDITIONAL_SET_FLAG(bc & 0x80000000, F_CF);
	CONDITIONAL_SET_FLAG(XOR2(bc >> 30), F_OF);
	CONDITIONAL_SET_FLAG(bc & 0x8, F_AF);
	return res;
}