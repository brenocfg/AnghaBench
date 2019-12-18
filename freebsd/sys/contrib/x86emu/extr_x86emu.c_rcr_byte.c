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
 scalar_t__ ACCESS_FLAG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 int XOR2 (int) ; 

__attribute__((used)) static uint8_t 
rcr_byte(struct x86emu *emu, uint8_t d, uint8_t s)
{
	uint32_t res, cnt;
	uint32_t mask, cf, ocf = 0;

	/* rotate right through carry */
	/* s is the rotate distance.  It varies from 0 - 8. d is the byte
	 * object rotated.
	 * 
	 * have
	 * 
	 * CF  B_7 B_6 B_5 B_4 B_3 B_2 B_1 B_0
	 * 
	 * The new rotate is done mod 9, and given this, for a rotation of n
	 * bits (mod 9) the new carry flag is then located n bits from the LSB.
	 * The low part is then shifted up cnt bits, and the high part is or'd
	 * in.  Using CAPS for new values, and lowercase for the original
	 * values, this can be expressed as:
	 * 
	 * IF n > 0 
	 *	1) CF <-  b_(n-1) 
	 *	2) B_(8-(n+1)) .. B_(0)  <-  b_(7) .. b_(n)
	 * 	3) B_(8-n) <- cf 4) B_(7) .. B_(8-(n-1)) <-  b_(n-2) .. b_(0)
	 */
	res = d;
	if ((cnt = s % 9) != 0) {
		/* extract the new CARRY FLAG. */
		/* CF <-  b_(n-1)              */
		if (cnt == 1) {
			cf = d & 0x1;
			/* note hackery here.  Access_flag(..) evaluates to
			 * either 0 if flag not set non-zero if flag is set.
			 * doing access_flag(..) != 0 casts that into either
			 * 0..1 in any representation of the flags register
			 * (i.e. packed bit array or unpacked.) */
			ocf = ACCESS_FLAG(F_CF) != 0;
		} else
			cf = (d >> (cnt - 1)) & 0x1;

		/* B_(8-(n+1)) .. B_(0)  <-  b_(7) .. b_n  */
		/* note that the right hand side done by the mask This is
		 * effectively done by shifting the object to the right.  The
		 * result must be masked, in case the object came in and was
		 * treated as a negative number.  Needed??? */

		mask = (1 << (8 - cnt)) - 1;
		res = (d >> cnt) & mask;

		/* now the high stuff which rotated around into the positions
		 * B_cnt-2 .. B_0 */
		/* B_(7) .. B_(8-(n-1)) <-  b_(n-2) .. b_(0) */
		/* shift it downward, 7-(n-2) = 9-n positions. and mask off
		 * the result before or'ing in. */
		res |= (d << (9 - cnt));

		/* if the carry flag was set, or it in.  */
		if (ACCESS_FLAG(F_CF)) {	/* carry flag is set */
			/* B_(8-n) <- cf */
			res |= 1 << (8 - cnt);
		}
		/* set the new carry flag, based on the variable "cf" */
		CONDITIONAL_SET_FLAG(cf, F_CF);
		/* OVERFLOW is set *IFF* cnt==1, then it is the xor of CF and
		 * the most significant bit.  Blecck. */
		/* parenthesized... */
		if (cnt == 1) {
			CONDITIONAL_SET_FLAG(XOR2(ocf + ((d >> 6) & 0x2)),
			    F_OF);
		}
	}
	return (uint8_t) res;
}