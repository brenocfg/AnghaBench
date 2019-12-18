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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Cell ;
typedef  double Awkfloat ;

/* Variables and functions */
#define  ADD 135 
#define  DIVIDE 134 
 int /*<<< orphan*/  FATAL (char*,...) ; 
#define  MINUS 133 
#define  MOD 132 
#define  MULT 131 
#define  POWER 130 
#define  UMINUS 129 
#define  UPLUS 128 
 double errcheck (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 double getfval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gettemp () ; 
 double ipow (double,int) ; 
 double modf (double,double*) ; 
 int /*<<< orphan*/  pow (double,double) ; 
 int /*<<< orphan*/  setfval (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *arith(Node **a, int n)	/* a[0] + a[1], etc.  also -a[0] */
{
	Awkfloat i, j = 0;
	double v;
	Cell *x, *y, *z;

	x = execute(a[0]);
	i = getfval(x);
	tempfree(x);
	if (n != UMINUS && n != UPLUS) {
		y = execute(a[1]);
		j = getfval(y);
		tempfree(y);
	}
	z = gettemp();
	switch (n) {
	case ADD:
		i += j;
		break;
	case MINUS:
		i -= j;
		break;
	case MULT:
		i *= j;
		break;
	case DIVIDE:
		if (j == 0)
			FATAL("division by zero");
		i /= j;
		break;
	case MOD:
		if (j == 0)
			FATAL("division by zero in mod");
		modf(i/j, &v);
		i = i - j * v;
		break;
	case UMINUS:
		i = -i;
		break;
    case UPLUS: /* handled by getfval(), above */
		break;
	case POWER:
		if (j >= 0 && modf(j, &v) == 0.0)	/* pos integer exponent */
			i = ipow(i, (int) j);
		else
			i = errcheck(pow(i, j), "pow");
		break;
	default:	/* can't happen */
		FATAL("illegal arithmetic operator %d", n);
	}
	setfval(z, i);
	return(z);
}