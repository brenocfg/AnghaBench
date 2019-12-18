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
typedef  int uint16_t ;
struct x86emu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_AF ; 
 int /*<<< orphan*/  F_OF ; 
 int /*<<< orphan*/  F_PF ; 
 int /*<<< orphan*/  F_SF ; 
 int /*<<< orphan*/  F_ZF ; 
 int PARITY (int) ; 
 int XOR2 (int) ; 

__attribute__((used)) static uint16_t 
inc_word(struct x86emu *emu, uint16_t d)
{
	uint32_t res;	/* all operands in native machine order */
	uint32_t cc;

	res = d + 1;
	CONDITIONAL_SET_FLAG((res & 0xffff) == 0, F_ZF);
	CONDITIONAL_SET_FLAG(res & 0x8000, F_SF);
	CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);

	/* calculate the carry chain  SEE NOTE AT TOP. */
	cc = (1 & d) | ((~res) & (1 | d));
	CONDITIONAL_SET_FLAG(XOR2(cc >> 14), F_OF);
	CONDITIONAL_SET_FLAG(cc & 0x8, F_AF);
	return (uint16_t) res;
}