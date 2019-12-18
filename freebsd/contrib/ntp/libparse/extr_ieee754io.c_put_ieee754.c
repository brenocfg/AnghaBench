#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int /*<<< orphan*/  offsets_t ;
struct TYPE_6__ {int l_ui; unsigned long l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 int IEEE_BADCALL ; 
#define  IEEE_DOUBLE 129 
 int IEEE_OK ; 
#define  IEEE_SINGLE 128 
 scalar_t__ L_ISNEG (TYPE_1__*) ; 
 scalar_t__ L_ISZERO (TYPE_1__*) ; 
 int /*<<< orphan*/  L_NEG (TYPE_1__*) ; 
 int debug ; 
 char* fmt_flt (unsigned int,int,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int
put_ieee754(
	    unsigned char **bufpp,
	    int size,
	    l_fp *lfpp,
	    offsets_t offsets
	    )
{
  l_fp outlfp;
#ifdef LIBDEBUG
  unsigned int sign;
  unsigned int bias;
#endif
/*unsigned int maxexp;*/
  int mbits;
  int msb;
  u_long mantissa_low = 0;
  u_long mantissa_high = 0;
#ifdef LIBDEBUG
  u_long characteristic = 0;
  long exponent;
#endif
/*int length;*/
  unsigned long mask;
  
  outlfp = *lfpp;

  switch (size)
    {
    case IEEE_DOUBLE:
    /*length = 8;*/
      mbits  = 52;
#ifdef LIBDEBUG
      bias   = 1023;
#endif
    /*maxexp = 2047;*/
      break;

    case IEEE_SINGLE:
    /*length = 4;*/
      mbits  = 23;
#ifdef LIBDEBUG
      bias   = 127;
#endif
    /*maxexp = 255;*/
      break;

    default:
      return IEEE_BADCALL;
    }
  
  /*
   * find sign
   */
  if (L_ISNEG(&outlfp))
    {
      L_NEG(&outlfp);
#ifdef LIBDEBUG
      sign = 1;
#endif
    }
  else
    {
#ifdef LIBDEBUG
      sign = 0;
#endif
    }

  if (L_ISZERO(&outlfp))
    {
#ifdef LIBDEBUG
      exponent = mantissa_high = mantissa_low = 0; /* true zero */
#endif
    }
  else
    {
      /*
       * find number of significant integer bits
       */
      mask = 0x80000000;
      if (outlfp.l_ui)
	{
	  msb = 63;
	  while (mask && ((outlfp.l_ui & mask) == 0))
	    {
	      mask >>= 1;
	      msb--;
	    }
	}
      else
	{
	  msb = 31;
	  while (mask && ((outlfp.l_uf & mask) == 0))
	    {
	      mask >>= 1;
	      msb--;
	    }
	}
  
      switch (size)
	{
	case IEEE_SINGLE:
	  mantissa_high = 0;
	  if (msb >= 32)
	    {
	      mantissa_low  = (outlfp.l_ui & ((1 << (msb - 32)) - 1)) << (mbits - (msb - 32));
	      mantissa_low |=  outlfp.l_uf >> (mbits - (msb - 32));
	    }
	  else
	    {
	      mantissa_low  = (outlfp.l_uf << (mbits - msb)) & ((1 << mbits) - 1);
	    }
	  break;
	  
	case IEEE_DOUBLE:
	  if (msb >= 32)
	    {
	      mantissa_high  = (outlfp.l_ui << (mbits - msb)) & ((1 << (mbits - 32)) - 1);
	      mantissa_high |=  outlfp.l_uf >> (32 - (mbits - msb));
	      mantissa_low   = (outlfp.l_ui & ((1 << (msb - mbits)) - 1)) << (32 - (msb - mbits));
	      mantissa_low  |=  outlfp.l_uf >> (msb - mbits);
	    }
	  else
	    {
	      mantissa_high  = outlfp.l_uf << (mbits - 32 - msb);
	      mantissa_low   = outlfp.l_uf << (mbits - 32);
	    }
	}

#ifdef LIBDEBUG
      exponent = msb - 32;
      characteristic = exponent + bias;

      if (debug > 4)
	printf("FP: %s\n", fmt_flt(sign, mantissa_high, mantissa_low, characteristic));
#endif
    }
  return IEEE_OK;
}