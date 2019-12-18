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
union ieee754sp {int bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPXSP ; 
 int /*<<< orphan*/  COMPYSP ; 
 int /*<<< orphan*/  EXPLODEXSP ; 
 int /*<<< orphan*/  EXPLODEYSP ; 
 int /*<<< orphan*/  FLUSHXSP ; 
 int /*<<< orphan*/  FLUSHYSP ; 
 int IEEE754_CEQ ; 
 int IEEE754_CGT ; 
 scalar_t__ IEEE754_CLASS_SNAN ; 
 int IEEE754_CLT ; 
 int IEEE754_CUN ; 
 int /*<<< orphan*/  IEEE754_INVALID_OPERATION ; 
 int SP_SIGN_BIT ; 
 scalar_t__ ieee754_class_nan (scalar_t__) ; 
 int /*<<< orphan*/  ieee754_clearcx () ; 
 int /*<<< orphan*/  ieee754_setcx (int /*<<< orphan*/ ) ; 
 scalar_t__ xc ; 
 scalar_t__ yc ; 

int ieee754sp_cmp(union ieee754sp x, union ieee754sp y, int cmp, int sig)
{
	int vx;
	int vy;

	COMPXSP;
	COMPYSP;

	EXPLODEXSP;
	EXPLODEYSP;
	FLUSHXSP;
	FLUSHYSP;
	ieee754_clearcx();	/* Even clear inexact flag here */

	if (ieee754_class_nan(xc) || ieee754_class_nan(yc)) {
		if (sig ||
		    xc == IEEE754_CLASS_SNAN || yc == IEEE754_CLASS_SNAN)
			ieee754_setcx(IEEE754_INVALID_OPERATION);
		return (cmp & IEEE754_CUN) != 0;
	} else {
		vx = x.bits;
		vy = y.bits;

		if (vx < 0)
			vx = -vx ^ SP_SIGN_BIT;
		if (vy < 0)
			vy = -vy ^ SP_SIGN_BIT;

		if (vx < vy)
			return (cmp & IEEE754_CLT) != 0;
		else if (vx == vy)
			return (cmp & IEEE754_CEQ) != 0;
		else
			return (cmp & IEEE754_CGT) != 0;
	}
}