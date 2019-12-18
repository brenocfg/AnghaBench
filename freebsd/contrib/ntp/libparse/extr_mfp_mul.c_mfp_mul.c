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
typedef  int u_long ;
typedef  int u_int32 ;
typedef  int int32 ;

/* Variables and functions */
 int FRACTION_PREC ; 
 int HIGH_MASK ; 
 int LOW_MASK ; 
 int /*<<< orphan*/  M_NEG (int,int) ; 
 int debug ; 
 char* mfptoa (int,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
mfp_mul(
	int32   *o_i,
	u_int32 *o_f,
	int32    a_i,
	u_int32  a_f,
	int32    b_i,
	u_int32  b_f
	)
{
  int32 i, j;
  u_int32  f;
  u_long a[4];			/* operand a */
  u_long b[4];			/* operand b */
  u_long c[5];			/* result c - 5 items for performance - see below */
  u_long carry;
  
  int neg = 0;

  if (a_i < 0)			/* examine sign situation */
    {
      neg = 1;
      M_NEG(a_i, a_f);
    }

  if (b_i < 0)			/* examine sign situation */
    {
      neg = !neg;
      M_NEG(b_i, b_f);
    }
  
  a[0] = a_f & LOW_MASK;	/* prepare a operand */
  a[1] = (a_f & HIGH_MASK) >> (FRACTION_PREC/2);
  a[2] = a_i & LOW_MASK;
  a[3] = (a_i & HIGH_MASK) >> (FRACTION_PREC/2);
  
  b[0] = b_f & LOW_MASK;	/* prepare b operand */
  b[1] = (b_f & HIGH_MASK) >> (FRACTION_PREC/2);
  b[2] = b_i & LOW_MASK;
  b[3] = (b_i & HIGH_MASK) >> (FRACTION_PREC/2);

  c[0] = c[1] = c[2] = c[3] = c[4] = 0;

  for (i = 0; i < 4; i++)	/* we do assume 32 * 32 = 64 bit multiplication */
    for (j = 0; j < 4; j++)
      {
	u_long result_low, result_high;
	int low_index = (i+j)/2;      /* formal [0..3]  - index for low long word */
	int mid_index = 1+low_index;  /* formal [1..4]! - index for high long word
					 will generate unecessary add of 0 to c[4]
					 but save 15 'if (result_high) expressions' */
	int high_index = 1+mid_index; /* formal [2..5]! - index for high word overflow
					 - only assigned on overflow (limits range to 2..3) */

	result_low = (u_long)a[i] * (u_long)b[j];	/* partial product */

	if ((i+j) & 1)		/* splits across two result registers */
	  {
	    result_high   = result_low >> (FRACTION_PREC/2);
	    result_low  <<= FRACTION_PREC/2;
	    carry         = (unsigned)1<<(FRACTION_PREC/2);
	  }
	else
	  {			/* stays in a result register - except for overflows */
	    result_high = 0;
	    carry       = 1;
	  }

	if (((c[low_index] >> 1) + (result_low >> 1) + ((c[low_index] & result_low & carry) != 0)) &
	    (u_int32)((unsigned)1<<(FRACTION_PREC - 1))) {
	  result_high++;	/* propagate overflows */
        }

	c[low_index]   += result_low; /* add up partial products */

	if (((c[mid_index] >> 1) + (result_high >> 1) + ((c[mid_index] & result_high & 1) != 0)) &
	    (u_int32)((unsigned)1<<(FRACTION_PREC - 1))) {
	  c[high_index]++;		/* propagate overflows of high word sum */
        }

	c[mid_index] += result_high;  /* will add a 0 to c[4] once but saves 15 if conditions */
      }

#ifdef DEBUG
  if (debug > 6)
    printf("mfp_mul: 0x%04lx%04lx%04lx%04lx * 0x%04lx%04lx%04lx%04lx = 0x%08lx%08lx%08lx%08lx\n",
	 a[3], a[2], a[1], a[0], b[3], b[2], b[1], b[0], c[3], c[2], c[1], c[0]);
#endif

  if (c[3])			/* overflow */
    {
      i = ((unsigned)1 << (FRACTION_PREC-1)) - 1;
      f = ~(unsigned)0;
    }
  else
    {				/* take produkt - discarding extra precision */
      i = c[2];
      f = c[1];
    }
  
  if (neg)			/* recover sign */
    {
      M_NEG(i, f);
    }

  *o_i = i;
  *o_f = f;

#ifdef DEBUG
  if (debug > 6)
    printf("mfp_mul: %s * %s => %s\n",
	   mfptoa((u_long)a_i, a_f, 6),
	   mfptoa((u_long)b_i, b_f, 6),
	   mfptoa((u_long)i, f, 6));
#endif
}