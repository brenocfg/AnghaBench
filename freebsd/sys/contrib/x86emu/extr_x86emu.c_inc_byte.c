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
typedef  int uint8_t ;
typedef  int uint32_t ;
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

__attribute__((used)) static uint8_t 
inc_byte(struct x86emu *emu, uint8_t d)
{
	uint32_t res;	/* all operands in native machine order */
	uint32_t cc;

	res = d + 1;
	CONDITIONAL_SET_FLAG((res & 0xff) == 0, F_ZF);
	CONDITIONAL_SET_FLAG(res & 0x80, F_SF);
	CONDITIONAL_SET_FLAG(PARITY(res & 0xff), F_PF);

	/* calculate the carry chain  SEE NOTE AT TOP. */
	cc = ((1 & d) | (~res)) & (1 | d);
	CONDITIONAL_SET_FLAG(XOR2(cc >> 6), F_OF);
	CONDITIONAL_SET_FLAG(cc & 0x8, F_AF);
	return (uint8_t) res;
}