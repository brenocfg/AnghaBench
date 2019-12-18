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
struct ui_file {int dummy; } ;

/* Variables and functions */
 scalar_t__ BFD_ENDIAN_BIG ; 
 unsigned int BITS_IN_BYTES ; 
 unsigned int BITS_IN_OCTAL ; 
 unsigned char CARRY_ONE ; 
 unsigned char CARRY_ZERO ; 
 unsigned char HIGH_ONE ; 
 unsigned char HIGH_TWO ; 
 unsigned char HIGH_ZERO ; 
 unsigned char LOW_ONE ; 
 unsigned char LOW_TWO ; 
 unsigned char LOW_ZERO ; 
 unsigned char MID_ONE ; 
 unsigned char MID_TWO ; 
 scalar_t__ TARGET_BYTE_ORDER ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*,unsigned char) ; 
 int /*<<< orphan*/  fputs_filtered (int /*<<< orphan*/ ,struct ui_file*) ; 
 int /*<<< orphan*/  local_octal_format_prefix () ; 
 int /*<<< orphan*/  local_octal_format_suffix () ; 

void
print_octal_chars (struct ui_file *stream, unsigned char *valaddr, unsigned len)
{
  unsigned char *p;
  unsigned char octa1, octa2, octa3, carry;
  int cycle;

  /* FIXME: We should be not printing leading zeroes in most cases.  */


  /* Octal is 3 bits, which doesn't fit.  Yuk.  So we have to track
   * the extra bits, which cycle every three bytes:
   *
   * Byte side:       0            1             2          3
   *                         |             |            |            |
   * bit number   123 456 78 | 9 012 345 6 | 78 901 234 | 567 890 12 |
   *
   * Octal side:   0   1   carry  3   4  carry ...
   *
   * Cycle number:    0             1            2
   *
   * But of course we are printing from the high side, so we have to
   * figure out where in the cycle we are so that we end up with no
   * left over bits at the end.
   */
#define BITS_IN_OCTAL 3
#define HIGH_ZERO     0340
#define LOW_ZERO      0016
#define CARRY_ZERO    0003
#define HIGH_ONE      0200
#define MID_ONE       0160
#define LOW_ONE       0016
#define CARRY_ONE     0001
#define HIGH_TWO      0300
#define MID_TWO       0070
#define LOW_TWO       0007

  /* For 32 we start in cycle 2, with two bits and one bit carry;
   * for 64 in cycle in cycle 1, with one bit and a two bit carry.
   */
  cycle = (len * BITS_IN_BYTES) % BITS_IN_OCTAL;
  carry = 0;

  fputs_filtered (local_octal_format_prefix (), stream);
  if (TARGET_BYTE_ORDER == BFD_ENDIAN_BIG)
    {
      for (p = valaddr;
	   p < valaddr + len;
	   p++)
	{
	  switch (cycle)
	    {
	    case 0:
	      /* No carry in, carry out two bits.
	       */
	      octa1 = (HIGH_ZERO & *p) >> 5;
	      octa2 = (LOW_ZERO & *p) >> 2;
	      carry = (CARRY_ZERO & *p);
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      break;

	    case 1:
	      /* Carry in two bits, carry out one bit.
	       */
	      octa1 = (carry << 1) | ((HIGH_ONE & *p) >> 7);
	      octa2 = (MID_ONE & *p) >> 4;
	      octa3 = (LOW_ONE & *p) >> 1;
	      carry = (CARRY_ONE & *p);
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      fprintf_filtered (stream, "%o", octa3);
	      break;

	    case 2:
	      /* Carry in one bit, no carry out.
	       */
	      octa1 = (carry << 2) | ((HIGH_TWO & *p) >> 6);
	      octa2 = (MID_TWO & *p) >> 3;
	      octa3 = (LOW_TWO & *p);
	      carry = 0;
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      fprintf_filtered (stream, "%o", octa3);
	      break;

	    default:
	      error ("Internal error in octal conversion;");
	    }

	  cycle++;
	  cycle = cycle % BITS_IN_OCTAL;
	}
    }
  else
    {
      for (p = valaddr + len - 1;
	   p >= valaddr;
	   p--)
	{
	  switch (cycle)
	    {
	    case 0:
	      /* Carry out, no carry in */
	      octa1 = (HIGH_ZERO & *p) >> 5;
	      octa2 = (LOW_ZERO & *p) >> 2;
	      carry = (CARRY_ZERO & *p);
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      break;

	    case 1:
	      /* Carry in, carry out */
	      octa1 = (carry << 1) | ((HIGH_ONE & *p) >> 7);
	      octa2 = (MID_ONE & *p) >> 4;
	      octa3 = (LOW_ONE & *p) >> 1;
	      carry = (CARRY_ONE & *p);
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      fprintf_filtered (stream, "%o", octa3);
	      break;

	    case 2:
	      /* Carry in, no carry out */
	      octa1 = (carry << 2) | ((HIGH_TWO & *p) >> 6);
	      octa2 = (MID_TWO & *p) >> 3;
	      octa3 = (LOW_TWO & *p);
	      carry = 0;
	      fprintf_filtered (stream, "%o", octa1);
	      fprintf_filtered (stream, "%o", octa2);
	      fprintf_filtered (stream, "%o", octa3);
	      break;

	    default:
	      error ("Internal error in octal conversion;");
	    }

	  cycle++;
	  cycle = cycle % BITS_IN_OCTAL;
	}
    }

  fputs_filtered (local_octal_format_suffix (), stream);
}