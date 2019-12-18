#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int tval; double fval; } ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_1__ Cell ;
typedef  double Awkfloat ;

/* Variables and functions */
#define  ADDEQ 133 
 int ASSIGN ; 
#define  DIVEQ 132 
 int /*<<< orphan*/  FATAL (char*,...) ; 
 int FLD ; 
#define  MODEQ 131 
#define  MULTEQ 130 
 int NUM ; 
#define  POWEQ 129 
 int REC ; 
 int STR ; 
#define  SUBEQ 128 
 double errcheck (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* execute (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  funnyvar (TYPE_1__*,char*) ; 
 double getfval (TYPE_1__*) ; 
 int /*<<< orphan*/  getsval (TYPE_1__*) ; 
 double ipow (double,int) ; 
 scalar_t__ isnum (TYPE_1__*) ; 
 scalar_t__ isstr (TYPE_1__*) ; 
 double modf (double,double*) ; 
 TYPE_1__* nfloc ; 
 int /*<<< orphan*/  pow (double,double) ; 
 int /*<<< orphan*/  setfval (TYPE_1__*,double) ; 
 int /*<<< orphan*/  setsval (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempfree (TYPE_1__*) ; 

Cell *assign(Node **a, int n)	/* a[0] = a[1], a[0] += a[1], etc. */
{		/* this is subtle; don't muck with it. */
	Cell *x, *y;
	Awkfloat xf, yf;
	double v;

	y = execute(a[1]);
	x = execute(a[0]);
	if (n == ASSIGN) {	/* ordinary assignment */
		if (x == y && !(x->tval & (FLD|REC)) && x != nfloc)
			;	/* self-assignment: leave alone unless it's a field or NF */
		else if ((y->tval & (STR|NUM)) == (STR|NUM)) {
			setsval(x, getsval(y));
			x->fval = getfval(y);
			x->tval |= NUM;
		}
		else if (isstr(y))
			setsval(x, getsval(y));
		else if (isnum(y))
			setfval(x, getfval(y));
		else
			funnyvar(y, "read value of");
		tempfree(y);
		return(x);
	}
	xf = getfval(x);
	yf = getfval(y);
	switch (n) {
	case ADDEQ:
		xf += yf;
		break;
	case SUBEQ:
		xf -= yf;
		break;
	case MULTEQ:
		xf *= yf;
		break;
	case DIVEQ:
		if (yf == 0)
			FATAL("division by zero in /=");
		xf /= yf;
		break;
	case MODEQ:
		if (yf == 0)
			FATAL("division by zero in %%=");
		modf(xf/yf, &v);
		xf = xf - yf * v;
		break;
	case POWEQ:
		if (yf >= 0 && modf(yf, &v) == 0.0)	/* pos integer exponent */
			xf = ipow(xf, (int) yf);
		else
			xf = errcheck(pow(xf, yf), "pow");
		break;
	default:
		FATAL("illegal assignment operator %d", n);
		break;
	}
	tempfree(y);
	setfval(x, xf);
	return(x);
}