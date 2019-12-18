#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int exp; int manh; int manl; int /*<<< orphan*/  sign; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;

/* Variables and functions */
 int LDBL_NBIT ; 
 int /*<<< orphan*/  mask_nbit_l (union IEEEl2bits) ; 

long double
nextafterl(long double x, long double y)
{
	volatile long double t;
	union IEEEl2bits ux, uy;

	ux.e = x;
	uy.e = y;

	if ((ux.bits.exp == 0x7fff &&
	     ((ux.bits.manh&~LDBL_NBIT)|ux.bits.manl) != 0) ||
	    (uy.bits.exp == 0x7fff &&
	     ((uy.bits.manh&~LDBL_NBIT)|uy.bits.manl) != 0))
	   return x+y;	/* x or y is nan */
	if(x==y) return y;		/* x=y, return y */
	if(x==0.0) {
	    ux.bits.manh = 0;			/* return +-minsubnormal */
	    ux.bits.manl = 1;
	    ux.bits.sign = uy.bits.sign;
	    t = ux.e*ux.e;
	    if(t==ux.e) return t; else return ux.e; /* raise underflow flag */
	}
	if(x>0.0 ^ x<y) {			/* x -= ulp */
	    if(ux.bits.manl==0) {
		if ((ux.bits.manh&~LDBL_NBIT)==0)
		    ux.bits.exp -= 1;
		ux.bits.manh = (ux.bits.manh - 1) | (ux.bits.manh & LDBL_NBIT);
	    }
	    ux.bits.manl -= 1;
	} else {				/* x += ulp */
	    ux.bits.manl += 1;
	    if(ux.bits.manl==0) {
		ux.bits.manh = (ux.bits.manh + 1) | (ux.bits.manh & LDBL_NBIT);
		if ((ux.bits.manh&~LDBL_NBIT)==0)
		    ux.bits.exp += 1;
	    }
	}
	if(ux.bits.exp==0x7fff) return x+x;	/* overflow  */
	if(ux.bits.exp==0) {			/* underflow */
	    mask_nbit_l(ux);
	    t = ux.e * ux.e;
	    if(t!=ux.e)			/* raise underflow flag */
		return ux.e;
	}
	return ux.e;
}