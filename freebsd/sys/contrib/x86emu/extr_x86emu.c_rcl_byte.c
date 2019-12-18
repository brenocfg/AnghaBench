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
struct x86emu {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 scalar_t__ XOR2 (unsigned int) ; 

__attribute__((used)) static uint8_t 
rcl_byte(struct x86emu *emu, uint8_t d, uint8_t s)
{
	unsigned int res, cnt, mask, cf;

	/* s is the rotate distance.  It varies from 0 - 8. */
	/* have
	 * 
	 * CF  B_7 B_6 B_5 B_4 B_3 B_2 B_1 B_0
	 * 
	 * want to rotate through the carry by "s" bits.  We could loop, but
	 * that's inefficient.  So the width is 9, and we split into three
	 * parts:
	 * 
	 * The new carry flag   (was B_n) the stuff in B_n-1 .. B_0 the stuff
	 * in B_7 .. B_n+1
	 * 
	 * The new rotate is done mod 9, and given this, for a rotation of n
	 * bits (mod 9) the new carry flag is then located n bits from the MSB.
	 * The low part is then shifted up cnt bits, and the high part is or'd
	 * in.  Using CAPS for new values, and lowercase for the original
	 * values, this can be expressed as:
	 * 
	 * IF n > 0 1) CF <-  b_(8-n) 2) B_(7) .. B_(n)  <-  b_(8-(n+1)) .. b_0
	 * 3) B_(n-1) <- cf 4) B_(n-2) .. B_0 <-  b_7 .. b_(8-(n-1))
	 */
	res = d;
	if ((cnt = s % 9) != 0) {
		/* extract the new CARRY FLAG. */
		/* CF <-  b_(8-n)             */
		cf = (d >> (8 - cnt)) & 0x1;

		/* 
		 * Get the low stuff which rotated into the range B_7 .. B_cnt
		 * B_(7) .. B_(n)  <-  b_(8-(n+1)) .. b_0
		 * note that the right hand side done by the mask.
		 */
		res = (d << cnt) & 0xff;

		/* 
		 * now the high stuff which rotated around into the positions
		 * B_cnt-2 .. B_0
		 * B_(n-2) .. B_0 <-  b_7 .. b_(8-(n-1))
		 * shift it downward, 7-(n-2) = 9-n positions. and mask off
		 * the result before or'ing in.
		 */
		mask = (1 << (cnt - 1)) - 1;
		res |= (d >> (9 - cnt)) & mask;

		/* if the carry flag was set, or it in.  */
		if (ACCESS_FLAG(F_CF)) {	/* carry flag is set */
			/* B_(n-1) <- cf */
			res |= 1 << (cnt - 1);
		}
		/* set the new carry flag, based on the variable "cf" */
		CONDITIONAL_SET_FLAG(cf, F_CF);
		/* OVERFLOW is set *IFF* cnt==1, then it is the xor of CF and
		 * the most significant bit.  Blecck. */
		/* parenthesized this expression since it appears to be
		 * causing OF to be misset */
		CONDITIONAL_SET_FLAG(cnt == 1 && XOR2(cf + ((res >> 6) & 0x2)),
		    F_OF);

	}
	return (uint8_t) res;
}