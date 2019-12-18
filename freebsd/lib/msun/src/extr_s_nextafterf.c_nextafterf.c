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
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLOAT_WORD (int,float) ; 
 int /*<<< orphan*/  SET_FLOAT_WORD (float,int) ; 

float
nextafterf(float x, float y)
{
	volatile float t;
	int32_t hx,hy,ix,iy;

	GET_FLOAT_WORD(hx,x);
	GET_FLOAT_WORD(hy,y);
	ix = hx&0x7fffffff;		/* |x| */
	iy = hy&0x7fffffff;		/* |y| */

	if((ix>0x7f800000) ||   /* x is nan */
	   (iy>0x7f800000))     /* y is nan */
	   return x+y;
	if(x==y) return y;		/* x=y, return y */
	if(ix==0) {				/* x == 0 */
	    SET_FLOAT_WORD(x,(hy&0x80000000)|1);/* return +-minsubnormal */
	    t = x*x;
	    if(t==x) return t; else return x;	/* raise underflow flag */
	}
	if(hx>=0) {				/* x > 0 */
	    if(hx>hy) {				/* x > y, x -= ulp */
		hx -= 1;
	    } else {				/* x < y, x += ulp */
		hx += 1;
	    }
	} else {				/* x < 0 */
	    if(hy>=0||hx>hy){			/* x < y, x -= ulp */
		hx -= 1;
	    } else {				/* x > y, x += ulp */
		hx += 1;
	    }
	}
	hy = hx&0x7f800000;
	if(hy>=0x7f800000) return x+x;	/* overflow  */
	if(hy<0x00800000) {		/* underflow */
	    t = x*x;
	    if(t!=x) {		/* raise underflow flag */
	        SET_FLOAT_WORD(y,hx);
		return y;
	    }
	}
	SET_FLOAT_WORD(x,hx);
	return x;
}