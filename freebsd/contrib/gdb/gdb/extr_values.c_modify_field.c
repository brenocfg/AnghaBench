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
typedef  int /*<<< orphan*/  oword ;
typedef  int /*<<< orphan*/  fieldval ;
typedef  int ULONGEST ;
typedef  int LONGEST ;

/* Variables and functions */
 scalar_t__ BITS_BIG_ENDIAN ; 
 int extract_signed_integer (char*,int) ; 
 int /*<<< orphan*/  store_signed_integer (char*,int,int) ; 
 int /*<<< orphan*/  warning (char*,int) ; 

void
modify_field (char *addr, LONGEST fieldval, int bitpos, int bitsize)
{
  LONGEST oword;

  /* If a negative fieldval fits in the field in question, chop
     off the sign extension bits.  */
  if (bitsize < (8 * (int) sizeof (fieldval))
      && (~fieldval & ~((1 << (bitsize - 1)) - 1)) == 0)
    fieldval = fieldval & ((1 << bitsize) - 1);

  /* Warn if value is too big to fit in the field in question.  */
  if (bitsize < (8 * (int) sizeof (fieldval))
      && 0 != (fieldval & ~((1 << bitsize) - 1)))
    {
      /* FIXME: would like to include fieldval in the message, but
         we don't have a sprintf_longest.  */
      warning ("Value does not fit in %d bits.", bitsize);

      /* Truncate it, otherwise adjoining fields may be corrupted.  */
      fieldval = fieldval & ((1 << bitsize) - 1);
    }

  oword = extract_signed_integer (addr, sizeof oword);

  /* Shifting for bit field depends on endianness of the target machine.  */
  if (BITS_BIG_ENDIAN)
    bitpos = sizeof (oword) * 8 - bitpos - bitsize;

  /* Mask out old value, while avoiding shifts >= size of oword */
  if (bitsize < 8 * (int) sizeof (oword))
    oword &= ~(((((ULONGEST) 1) << bitsize) - 1) << bitpos);
  else
    oword &= ~((~(ULONGEST) 0) << bitpos);
  oword |= fieldval << bitpos;

  store_signed_integer (addr, sizeof oword, oword);
}