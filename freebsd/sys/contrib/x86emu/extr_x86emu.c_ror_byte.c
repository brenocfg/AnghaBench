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
 int /*<<< orphan*/  CONDITIONAL_SET_FLAG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_CF ; 
 int /*<<< orphan*/  F_OF ; 
 scalar_t__ XOR2 (unsigned int) ; 

__attribute__((used)) static uint8_t 
ror_byte(struct x86emu *emu, uint8_t d, uint8_t s)
{
	unsigned int res, cnt, mask;

	/* rotate right */
	/* s is the rotate distance.  It varies from 0 - 8. d is the byte
	 * object rotated.
	 * 
	 * have
	 * 
	 * B_7 ... B_0
	 * 
	 * The rotate is done mod 8.
	 * 
	 * IF n > 0 1) B_(8-(n+1)) .. B_(0)  <-  b_(7) .. b_(n) 2) B_(7) ..
	 * B_(8-n) <-  b_(n-1) .. b_(0) */
	res = d;
	if ((cnt = s % 8) != 0) {	/* not a typo, do nada if cnt==0 */
		/* B_(7) .. B_(8-n) <-  b_(n-1) .. b_(0) */
		res = (d << (8 - cnt));

		/* B_(8-(n+1)) .. B_(0)  <-  b_(7) .. b_(n) */
		mask = (1 << (8 - cnt)) - 1;
		res |= (d >> (cnt)) & mask;

		/* OVERFLOW is set *IFF* s==1, then it is the xor of the two
		 * most significant bits.  Blecck. */
		CONDITIONAL_SET_FLAG(s == 1 && XOR2(res >> 6), F_OF);
	}
	if (s != 0) {
		/* set the new carry flag, Note that it is the high order bit
		 * of the result!!!                               */
		CONDITIONAL_SET_FLAG(res & 0x80, F_CF);
	}
	return (uint8_t) res;
}