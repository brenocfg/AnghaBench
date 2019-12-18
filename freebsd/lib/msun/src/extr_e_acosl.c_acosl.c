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
typedef  int int16_t ;

/* Variables and functions */
 int ACOS_CONST ; 
 int BIAS ; 
 int LDBL_NBIT ; 
 long double P (long double) ; 
 long double Q (long double) ; 
 long double one ; 
 long double pi ; 
 long double pio2_hi ; 
 double pio2_lo ; 
 long double sqrtl (long double) ; 

long double
acosl(long double x)
{
	union IEEEl2bits u;
	long double z,p,q,r,w,s,c,df;
	int16_t expsign, expt;
	u.e = x;
	expsign = u.xbits.expsign;
	expt = expsign & 0x7fff;
	if(expt >= BIAS) {	/* |x| >= 1 */
	    if(expt==BIAS && ((u.bits.manh&~LDBL_NBIT)|u.bits.manl)==0) {
		if (expsign>0) return 0.0;	/* acos(1) = 0  */
		else return pi+2.0*pio2_lo;	/* acos(-1)= pi */
	    }
	    return (x-x)/(x-x);		/* acos(|x|>1) is NaN */
	}
	if(expt<BIAS-1) {	/* |x| < 0.5 */
	    if(expt<ACOS_CONST) return pio2_hi+pio2_lo;/*x tiny: acosl=pi/2*/
	    z = x*x;
	    p = P(z);
	    q = Q(z);
	    r = p/q;
	    return pio2_hi - (x - (pio2_lo-x*r));
	} else  if (expsign<0) {	/* x < -0.5 */
	    z = (one+x)*0.5;
	    p = P(z);
	    q = Q(z);
	    s = sqrtl(z);
	    r = p/q;
	    w = r*s-pio2_lo;
	    return pi - 2.0*(s+w);
	} else {			/* x > 0.5 */
	    z = (one-x)*0.5;
	    s = sqrtl(z);
	    u.e = s;
	    u.bits.manl = 0;
	    df = u.e;
	    c  = (z-df*df)/(s+df);
	    p = P(z);
	    q = Q(z);
	    r = p/q;
	    w = r*s+c;
	    return 2.0*(df+w);
	}
}