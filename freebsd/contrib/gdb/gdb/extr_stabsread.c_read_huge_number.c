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

/* Variables and functions */
 int LONG_MAX ; 

__attribute__((used)) static long
read_huge_number (char **pp, int end, int *bits)
{
  char *p = *pp;
  int sign = 1;
  long n = 0;
  int radix = 10;
  char overflow = 0;
  int nbits = 0;
  int c;
  long upper_limit;

  if (*p == '-')
    {
      sign = -1;
      p++;
    }

  /* Leading zero means octal.  GCC uses this to output values larger
     than an int (because that would be hard in decimal).  */
  if (*p == '0')
    {
      radix = 8;
      p++;
    }

  upper_limit = LONG_MAX / radix;

  while ((c = *p++) >= '0' && c < ('0' + radix))
    {
      if (n <= upper_limit)
	{
	  n *= radix;
	  n += c - '0';		/* FIXME this overflows anyway */
	}
      else
	overflow = 1;

      /* This depends on large values being output in octal, which is
         what GCC does. */
      if (radix == 8)
	{
	  if (nbits == 0)
	    {
	      if (c == '0')
		/* Ignore leading zeroes.  */
		;
	      else if (c == '1')
		nbits = 1;
	      else if (c == '2' || c == '3')
		nbits = 2;
	      else
		nbits = 3;
	    }
	  else
	    nbits += 3;
	}
    }
  if (end)
    {
      if (c && c != end)
	{
	  if (bits != NULL)
	    *bits = -1;
	  return 0;
	}
    }
  else
    --p;

  *pp = p;
  if (overflow)
    {
      if (nbits == 0)
	{
	  /* Large decimal constants are an error (because it is hard to
	     count how many bits are in them).  */
	  if (bits != NULL)
	    *bits = -1;
	  return 0;
	}

      /* -0x7f is the same as 0x80.  So deal with it by adding one to
         the number of bits.  */
      if (sign == -1)
	++nbits;
      if (bits)
	*bits = nbits;
    }
  else
    {
      if (bits)
	*bits = 0;
      return n * sign;
    }
  /* It's *BITS which has the interesting information.  */
  return 0;
}