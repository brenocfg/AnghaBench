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
 float __ieee754_sqrtf (float) ; 
 float fabsf (float) ; 
 float fabsl (float) ; 

float
__ieee754_hypotf(float x, float y)
{
	float a,b,t1,t2,y1,y2,w;
	int32_t j,k,ha,hb;

	GET_FLOAT_WORD(ha,x);
	ha &= 0x7fffffff;
	GET_FLOAT_WORD(hb,y);
	hb &= 0x7fffffff;
	if(hb > ha) {a=y;b=x;j=ha; ha=hb;hb=j;} else {a=x;b=y;}
	a = fabsf(a);
	b = fabsf(b);
	if((ha-hb)>0xf000000) {return a+b;} /* x/y > 2**30 */
	k=0;
	if(ha > 0x58800000) {	/* a>2**50 */
	   if(ha >= 0x7f800000) {	/* Inf or NaN */
	       /* Use original arg order iff result is NaN; quieten sNaNs. */
	       w = fabsl(x+0.0L)-fabsf(y+0);
	       if(ha == 0x7f800000) w = a;
	       if(hb == 0x7f800000) w = b;
	       return w;
	   }
	   /* scale a and b by 2**-68 */
	   ha -= 0x22000000; hb -= 0x22000000;	k += 68;
	   SET_FLOAT_WORD(a,ha);
	   SET_FLOAT_WORD(b,hb);
	}
	if(hb < 0x26800000) {	/* b < 2**-50 */
	    if(hb <= 0x007fffff) {	/* subnormal b or 0 */
	        if(hb==0) return a;
		SET_FLOAT_WORD(t1,0x7e800000);	/* t1=2^126 */
		b *= t1;
		a *= t1;
		k -= 126;
	    } else {		/* scale a and b by 2^68 */
	        ha += 0x22000000; 	/* a *= 2^68 */
		hb += 0x22000000;	/* b *= 2^68 */
		k -= 68;
		SET_FLOAT_WORD(a,ha);
		SET_FLOAT_WORD(b,hb);
	    }
	}
    /* medium size a and b */
	w = a-b;
	if (w>b) {
	    SET_FLOAT_WORD(t1,ha&0xfffff000);
	    t2 = a-t1;
	    w  = __ieee754_sqrtf(t1*t1-(b*(-b)-t2*(a+t1)));
	} else {
	    a  = a+a;
	    SET_FLOAT_WORD(y1,hb&0xfffff000);
	    y2 = b - y1;
	    SET_FLOAT_WORD(t1,(ha+0x00800000)&0xfffff000);
	    t2 = a - t1;
	    w  = __ieee754_sqrtf(t1*y1-(w*(-w)-(t1*y2+t2*b)));
	}
	if(k!=0) {
	    SET_FLOAT_WORD(t1,0x3f800000+(k<<23));
	    return t1*w;
	} else return w;
}