#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int* offsets_t ;
struct TYPE_5__ {int l_ui; int l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int IEEE_BADCALL ; 
#define  IEEE_DOUBLE 129 
 int IEEE_NAN ; 
 int IEEE_NEGINFINITY ; 
 int IEEE_NEGOVERFLOW ; 
 int IEEE_OK ; 
 int IEEE_POSINFINITY ; 
 int IEEE_POSOVERFLOW ; 
#define  IEEE_SINGLE 128 
 int /*<<< orphan*/  L_CLR (TYPE_1__*) ; 
 int /*<<< orphan*/  L_NEG (TYPE_1__*) ; 
 int debug ; 
 char* fmt_flt (unsigned int,int,int,int) ; 
 char* fmt_hex (unsigned char*,int) ; 
 int get_byte (unsigned char*,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,double,char*) ; 

int
fetch_ieee754(
	      unsigned char **buffpp,
	      int size,
	      l_fp *lfpp,
	      offsets_t offsets
	      )
{
  unsigned char *bufp = *buffpp;
  unsigned int sign;
  unsigned int bias;
  unsigned int maxexp;
  int mbits;
  u_long mantissa_low;
  u_long mantissa_high;
  u_long characteristic;
  long exponent;
#ifdef LIBDEBUG
  int length;
#endif
  unsigned char val;
  int fieldindex = 0;
  
  switch (size)
    {
    case IEEE_DOUBLE:
#ifdef LIBDEBUG
      length = 8;
#endif
      mbits  = 52;
      bias   = 1023;
      maxexp = 2047;
      break;

    case IEEE_SINGLE:
#ifdef LIBDEBUG
      length = 4;
#endif
      mbits  = 23;
      bias   = 127;
      maxexp = 255;
      break;

    default:
      return IEEE_BADCALL;
    }
  
  val = get_byte(bufp, offsets, &fieldindex); /* fetch sign byte & first part of characteristic */
  
  sign     = (val & 0x80) != 0;
  characteristic = (val & 0x7F);

  val = get_byte(bufp, offsets, &fieldindex); /* fetch rest of characteristic and start of mantissa */
  
  switch (size)
    {
    case IEEE_SINGLE:
      characteristic <<= 1;
      characteristic  |= (val & 0x80) != 0; /* grab last characteristic bit */

      mantissa_high  = 0;

      mantissa_low   = (val &0x7F) << 16;
      mantissa_low  |= (u_long)get_byte(bufp, offsets, &fieldindex) << 8;
      mantissa_low  |= get_byte(bufp, offsets, &fieldindex);
      break;
      
    case IEEE_DOUBLE:
      characteristic <<= 4;
      characteristic  |= (val & 0xF0) >> 4; /* grab lower characteristic bits */

      mantissa_high  = (val & 0x0F) << 16;
      mantissa_high |= (u_long)get_byte(bufp, offsets, &fieldindex) << 8;
      mantissa_high |= get_byte(bufp, offsets, &fieldindex);

      mantissa_low   = (u_long)get_byte(bufp, offsets, &fieldindex) << 24;
      mantissa_low  |= (u_long)get_byte(bufp, offsets, &fieldindex) << 16;
      mantissa_low  |= (u_long)get_byte(bufp, offsets, &fieldindex) << 8;
      mantissa_low  |= get_byte(bufp, offsets, &fieldindex);
      break;
      
    default:
      return IEEE_BADCALL;
    }
#ifdef LIBDEBUG
  if (debug > 4)
  {
    double d;
    float f;

    if (size == IEEE_SINGLE)
      {
	int i;

	for (i = 0; i < length; i++)
	  {
	    *((unsigned char *)(&f)+i) = *(*buffpp + offsets[i]);
	  }
	d = f;
      }
    else
      {
	int i;

	for (i = 0; i < length; i++)
	  {
	    *((unsigned char *)(&d)+i) = *(*buffpp + offsets[i]);
	  }
      }
    
    printf("fetchieee754: FP: %s -> %s -> %e(=%s)\n", fmt_hex(*buffpp, length),
	   fmt_flt(sign, mantissa_high, mantissa_low, characteristic),
	   d, fmt_hex((unsigned char *)&d, length));
  }
#endif

  *buffpp += fieldindex;
  
  /*
   * detect funny numbers
   */
  if (characteristic == maxexp)
    {
      /*
       * NaN or Infinity
       */
      if (mantissa_low || mantissa_high)
	{
	  /*
	   * NaN
	   */
	  return IEEE_NAN;
	}
      else
	{
	  /*
	   * +Inf or -Inf
	   */
	  return sign ? IEEE_NEGINFINITY : IEEE_POSINFINITY;
	}
    }
  else
    {
      /*
       * collect real numbers
       */

      L_CLR(lfpp);

      /*
       * check for overflows
       */
      exponent = characteristic - bias;

      if (exponent > 31)	/* sorry - hardcoded */
	{
	  /*
	   * overflow only in respect to NTP-FP representation
	   */
	  return sign ? IEEE_NEGOVERFLOW : IEEE_POSOVERFLOW;
	}
      else
	{
	  int frac_offset;	/* where the fraction starts */
	  
	  frac_offset = mbits - exponent;

	  if (characteristic == 0) 
	    {
	      /*
	       * de-normalized or tiny number - fits only as 0
	       */
	      return IEEE_OK;
	    }
	  else
	    {
	      /*
	       * adjust for implied 1
	       */
	      if (mbits > 31)
		mantissa_high |= 1 << (mbits - 32);
	      else
		mantissa_low  |= 1 << mbits;

	      /*
	       * take mantissa apart - if only all machine would support
	       * 64 bit operations 8-(
	       */
	      if (frac_offset > mbits)
		{
		  lfpp->l_ui = 0; /* only fractional number */
		  frac_offset -= mbits + 1; /* will now contain right shift count - 1*/
		  if (mbits > 31)
		    {
		      lfpp->l_uf   = mantissa_high << (63 - mbits);
		      lfpp->l_uf  |= mantissa_low  >> (mbits - 33);
		      lfpp->l_uf >>= frac_offset;
		    }
		  else
		    {
		      lfpp->l_uf = mantissa_low >> frac_offset;
		    }
		}
	      else
		{
		  if (frac_offset > 32)
		    {
		      /*
		       * must split in high word
		       */
		      lfpp->l_ui  =  mantissa_high >> (frac_offset - 32);
		      lfpp->l_uf  = (mantissa_high & ((1 << (frac_offset - 32)) - 1)) << (64 - frac_offset);
		      lfpp->l_uf |=  mantissa_low  >> (frac_offset - 32);
		    }
		  else
		    {
		      /*
		       * must split in low word
		       */
		      lfpp->l_ui  =  mantissa_high << (32 - frac_offset);
		      lfpp->l_ui |= (mantissa_low >> frac_offset) & ((1 << (32 - frac_offset)) - 1);
		      lfpp->l_uf  = (mantissa_low & ((1 << frac_offset) - 1)) << (32 - frac_offset);
		    }
		}
	      
	      /*
	       * adjust for sign
	       */
	      if (sign)
		{
		  L_NEG(lfpp);
		}
	      
	      return IEEE_OK;
	    }
	}
    }
}