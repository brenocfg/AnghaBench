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
struct fpn {scalar_t__ fp_class; scalar_t__ fp_sign; } ;
struct fpemu {int fe_fpscr; int fe_cx; struct fpn fe_f3; struct fpn fe_f2; struct fpn fe_f1; } ;

/* Variables and functions */
 int FPSCR_FE ; 
 int FPSCR_FG ; 
 int FPSCR_FL ; 
 int FPSCR_FU ; 
 int FPSCR_VE ; 
 int FPSCR_VXSNAN ; 
 int FPSCR_VXVC ; 
 scalar_t__ ISINF (struct fpn*) ; 
 scalar_t__ ISNAN (struct fpn*) ; 
 scalar_t__ ISQNAN (struct fpn*) ; 
 scalar_t__ ISSNAN (struct fpn*) ; 
 scalar_t__ ISZERO (struct fpn*) ; 
 int diff (int) ; 
 int /*<<< orphan*/  fpu_sub (struct fpemu*) ; 

void
fpu_compare(struct fpemu *fe, int ordered)
{
	struct fpn *a, *b, *r;
	int cc;

	a = &fe->fe_f1;
	b = &fe->fe_f2;
	r = &fe->fe_f3;

	if (ISNAN(a) || ISNAN(b)) {
		/*
		 * In any case, we already got an exception for signalling
		 * NaNs; here we may replace that one with an identical
		 * exception, but so what?.
		 */
		cc = FPSCR_FU;
		if (ISSNAN(a) || ISSNAN(b))
			cc |= FPSCR_VXSNAN;
		if (ordered) {
			if (fe->fe_fpscr & FPSCR_VE || ISQNAN(a) || ISQNAN(b))
				cc |= FPSCR_VXVC;
		}
		goto done;
	}

	/*
	 * Must handle both-zero early to avoid sign goofs.  Otherwise,
	 * at most one is 0, and if the signs differ we are done.
	 */
	if (ISZERO(a) && ISZERO(b)) {
		cc = FPSCR_FE;
		goto done;
	}
	if (a->fp_sign) {		/* a < 0 (or -0) */
		if (!b->fp_sign) {	/* b >= 0 (or if a = -0, b > 0) */
			cc = FPSCR_FL;
			goto done;
		}
	} else {			/* a > 0 (or +0) */
		if (b->fp_sign) {	/* b <= -0 (or if a = +0, b < 0) */
			cc = FPSCR_FG;
			goto done;
		}
	}

	/*
	 * Now the signs are the same (but may both be negative).  All
	 * we have left are these cases:
	 *
	 *	|a| < |b|		[classes or values differ]
	 *	|a| > |b|		[classes or values differ]
	 *	|a| == |b|		[classes and values identical]
	 *
	 * We define `diff' here to expand these as:
	 *
	 *	|a| < |b|, a,b >= 0: a < b => FSR_CC_LT
	 *	|a| < |b|, a,b < 0:  a > b => FSR_CC_GT
	 *	|a| > |b|, a,b >= 0: a > b => FSR_CC_GT
	 *	|a| > |b|, a,b < 0:  a < b => FSR_CC_LT
	 */
#define opposite_cc(cc) ((cc) == FPSCR_FL ? FPSCR_FG : FPSCR_FL)
#define	diff(magnitude) (a->fp_sign ? opposite_cc(magnitude) :  (magnitude))
	if (a->fp_class < b->fp_class) {	/* |a| < |b| */
		cc = diff(FPSCR_FL);
		goto done;
	}
	if (a->fp_class > b->fp_class) {	/* |a| > |b| */
		cc = diff(FPSCR_FG);
		goto done;
	}
	/* now none can be 0: only Inf and numbers remain */
	if (ISINF(a)) {				/* |Inf| = |Inf| */
		cc = FPSCR_FE;
		goto done;
	}
	fpu_sub(fe);
	if (ISZERO(r))
		cc = FPSCR_FE;
	else if (r->fp_sign)
		cc = FPSCR_FL;
	else
		cc = FPSCR_FG;
done:
	fe->fe_cx = cc;
}