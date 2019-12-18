#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int manh; int manl; } ;
struct TYPE_3__ {int expsign; } ;
union IEEEl2bits {long double e; TYPE_2__ bits; TYPE_1__ xbits; } ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int BIAS ; 
 int LDBL_MANT_DIG ; 
 int LDBL_MAX_EXP ; 
 int LDBL_NBIT ; 
 long double atanl (long double) ; 
 long double fabsl (long double) ; 
 long double nan_mix (long double,long double) ; 
 long double pi ; 
 int /*<<< orphan*/  pi_lo ; 
 double pio2_hi ; 
 double pio2_lo ; 
 long double tiny ; 
 long double zero ; 

long double
atan2l(long double y, long double x)
{
	union IEEEl2bits ux, uy;
	long double z;
	int32_t k,m;
	int16_t exptx, expsignx, expty, expsigny;

	uy.e = y;
	expsigny = uy.xbits.expsign;
	expty = expsigny & 0x7fff;
	ux.e = x;
	expsignx = ux.xbits.expsign;
	exptx = expsignx & 0x7fff;

	if ((exptx==BIAS+LDBL_MAX_EXP &&
	     ((ux.bits.manh&~LDBL_NBIT)|ux.bits.manl)!=0) ||	/* x is NaN */
	    (expty==BIAS+LDBL_MAX_EXP &&
	     ((uy.bits.manh&~LDBL_NBIT)|uy.bits.manl)!=0))	/* y is NaN */
	    return nan_mix(x, y);
	if (expsignx==BIAS && ((ux.bits.manh&~LDBL_NBIT)|ux.bits.manl)==0)
	    return atanl(y);					/* x=1.0 */
	m = ((expsigny>>15)&1)|((expsignx>>14)&2);	/* 2*sign(x)+sign(y) */

    /* when y = 0 */
	if(expty==0 && ((uy.bits.manh&~LDBL_NBIT)|uy.bits.manl)==0) {
	    switch(m) {
		case 0: 
		case 1: return y; 	/* atan(+-0,+anything)=+-0 */
		case 2: return  pi+tiny;/* atan(+0,-anything) = pi */
		case 3: return -pi-tiny;/* atan(-0,-anything) =-pi */
	    }
	}
    /* when x = 0 */
	if(exptx==0 && ((ux.bits.manh&~LDBL_NBIT)|ux.bits.manl)==0)
	    return (expsigny<0)?  -pio2_hi-tiny: pio2_hi+tiny;

    /* when x is INF */
	if(exptx==BIAS+LDBL_MAX_EXP) {
	    if(expty==BIAS+LDBL_MAX_EXP) {
		switch(m) {
		    case 0: return  pio2_hi*0.5+tiny;/* atan(+INF,+INF) */
		    case 1: return -pio2_hi*0.5-tiny;/* atan(-INF,+INF) */
		    case 2: return  1.5*pio2_hi+tiny;/*atan(+INF,-INF)*/
		    case 3: return -1.5*pio2_hi-tiny;/*atan(-INF,-INF)*/
		}
	    } else {
		switch(m) {
		    case 0: return  zero  ;	/* atan(+...,+INF) */
		    case 1: return -zero  ;	/* atan(-...,+INF) */
		    case 2: return  pi+tiny  ;	/* atan(+...,-INF) */
		    case 3: return -pi-tiny  ;	/* atan(-...,-INF) */
		}
	    }
	}
    /* when y is INF */
	if(expty==BIAS+LDBL_MAX_EXP)
	    return (expsigny<0)? -pio2_hi-tiny: pio2_hi+tiny;

    /* compute y/x */
	k = expty-exptx;
	if(k > LDBL_MANT_DIG+2) {			/* |y/x| huge */
	    z=pio2_hi+pio2_lo;
	    m&=1;
	}
	else if(expsignx<0&&k<-LDBL_MANT_DIG-2) z=0.0; 	/* |y/x| tiny, x<0 */
	else z=atanl(fabsl(y/x));		/* safe to do y/x */
	switch (m) {
	    case 0: return       z  ;	/* atan(+,+) */
	    case 1: return      -z  ;	/* atan(-,+) */
	    case 2: return  pi-(z-pi_lo);/* atan(+,-) */
	    default: /* case 3 */
	    	    return  (z-pi_lo)-pi;/* atan(-,-) */
	}
}