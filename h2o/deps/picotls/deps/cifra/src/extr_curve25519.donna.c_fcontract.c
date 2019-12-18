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
typedef  scalar_t__ u8 ;
typedef  int s32 ;
typedef  int limb ;

/* Variables and functions */
 int /*<<< orphan*/  F (int,int) ; 
 int s32_eq (int,int) ; 
 int s32_gte (int,int) ; 

__attribute__((used)) static void
fcontract(u8 *output, limb *input_limbs) {
  int i;
  int j;
  s32 input[10];
  s32 mask;

  /* |input_limbs[i]| < 2^26, so it's valid to convert to an s32. */
  for (i = 0; i < 10; i++) {
    input[i] = input_limbs[i];
  }

  for (j = 0; j < 2; ++j) {
    for (i = 0; i < 9; ++i) {
      if ((i & 1) == 1) {
        /* This calculation is a time-invariant way to make input[i]
         * non-negative by borrowing from the next-larger limb. */
        const s32 mask = input[i] >> 31;
        const s32 carry = -((input[i] & mask) >> 25);
        input[i] = input[i] + (carry << 25);
        input[i+1] = input[i+1] - carry;
      } else {
        const s32 mask = input[i] >> 31;
        const s32 carry = -((input[i] & mask) >> 26);
        input[i] = input[i] + (carry << 26);
        input[i+1] = input[i+1] - carry;
      }
    }

    /* There's no greater limb for input[9] to borrow from, but we can multiply
     * by 19 and borrow from input[0], which is valid mod 2^255-19. */
    {
      const s32 mask = input[9] >> 31;
      const s32 carry = -((input[9] & mask) >> 25);
      input[9] = input[9] + (carry << 25);
      input[0] = input[0] - (carry * 19);
    }

    /* After the first iteration, input[1..9] are non-negative and fit within
     * 25 or 26 bits, depending on position. However, input[0] may be
     * negative. */
  }

  /* The first borrow-propagation pass above ended with every limb
     except (possibly) input[0] non-negative.

     If input[0] was negative after the first pass, then it was because of a
     carry from input[9]. On entry, input[9] < 2^26 so the carry was, at most,
     one, since (2**26-1) >> 25 = 1. Thus input[0] >= -19.

     In the second pass, each limb is decreased by at most one. Thus the second
     borrow-propagation pass could only have wrapped around to decrease
     input[0] again if the first pass left input[0] negative *and* input[1]
     through input[9] were all zero.  In that case, input[1] is now 2^25 - 1,
     and this last borrow-propagation step will leave input[1] non-negative. */
  {
    const s32 mask = input[0] >> 31;
    const s32 carry = -((input[0] & mask) >> 26);
    input[0] = input[0] + (carry << 26);
    input[1] = input[1] - carry;
  }

  /* All input[i] are now non-negative. However, there might be values between
   * 2^25 and 2^26 in a limb which is, nominally, 25 bits wide. */
  for (j = 0; j < 2; j++) {
    for (i = 0; i < 9; i++) {
      if ((i & 1) == 1) {
        const s32 carry = input[i] >> 25;
        input[i] &= 0x1ffffff;
        input[i+1] += carry;
      } else {
        const s32 carry = input[i] >> 26;
        input[i] &= 0x3ffffff;
        input[i+1] += carry;
      }
    }

    {
      const s32 carry = input[9] >> 25;
      input[9] &= 0x1ffffff;
      input[0] += 19*carry;
    }
  }

  /* If the first carry-chain pass, just above, ended up with a carry from
   * input[9], and that caused input[0] to be out-of-bounds, then input[0] was
   * < 2^26 + 2*19, because the carry was, at most, two.
   *
   * If the second pass carried from input[9] again then input[0] is < 2*19 and
   * the input[9] -> input[0] carry didn't push input[0] out of bounds. */

  /* It still remains the case that input might be between 2^255-19 and 2^255.
   * In this case, input[1..9] must take their maximum value and input[0] must
   * be >= (2^255-19) & 0x3ffffff, which is 0x3ffffed. */
  mask = s32_gte(input[0], 0x3ffffed);
  for (i = 1; i < 10; i++) {
    if ((i & 1) == 1) {
      mask &= s32_eq(input[i], 0x1ffffff);
    } else {
      mask &= s32_eq(input[i], 0x3ffffff);
    }
  }

  /* mask is either 0xffffffff (if input >= 2^255-19) and zero otherwise. Thus
   * this conditionally subtracts 2^255-19. */
  input[0] -= mask & 0x3ffffed;

  for (i = 1; i < 10; i++) {
    if ((i & 1) == 1) {
      input[i] -= mask & 0x1ffffff;
    } else {
      input[i] -= mask & 0x3ffffff;
    }
  }

  input[1] <<= 2;
  input[2] <<= 3;
  input[3] <<= 5;
  input[4] <<= 6;
  input[6] <<= 1;
  input[7] <<= 3;
  input[8] <<= 4;
  input[9] <<= 6;
#define F(i, s) \
  output[s+0] |=  input[i] & 0xff; \
  output[s+1]  = (input[i] >> 8) & 0xff; \
  output[s+2]  = (input[i] >> 16) & 0xff; \
  output[s+3]  = (input[i] >> 24) & 0xff;
  output[0] = 0;
  output[16] = 0;
  F(0,0);
  F(1,3);
  F(2,6);
  F(3,9);
  F(4,12);
  F(5,16);
  F(6,19);
  F(7,22);
  F(8,25);
  F(9,28);
#undef F
}