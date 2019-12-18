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

/* Variables and functions */
 int ECCEN ; 
 double EPSILONg ; 
 double Nzero ; 
 int PI ; 
 double Pzero ; 
 double RHOg ; 
 int /*<<< orphan*/  adj360 (double*) ; 
 int cos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtor (double) ; 
 double lzero ; 
 double sin (int /*<<< orphan*/ ) ; 

__attribute__((used)) static double
potm(double days)
{
	double N, Msol, Ec, LambdaSol, l, Mm, Ev, Ac, A3, Mmprime;
	double A4, lprime, V, ldprime, D, Nm;

	N = 360 * days / 365.2422;				/* sec 42 #3 */
	adj360(&N);
	Msol = N + EPSILONg - RHOg;				/* sec 42 #4 */
	adj360(&Msol);
	Ec = 360 / PI * ECCEN * sin(dtor(Msol));		/* sec 42 #5 */
	LambdaSol = N + Ec + EPSILONg;				/* sec 42 #6 */
	adj360(&LambdaSol);
	l = 13.1763966 * days + lzero;				/* sec 61 #4 */
	adj360(&l);
	Mm = l - (0.1114041 * days) - Pzero;			/* sec 61 #5 */
	adj360(&Mm);
	Nm = Nzero - (0.0529539 * days);			/* sec 61 #6 */
	adj360(&Nm);
	Ev = 1.2739 * sin(dtor(2*(l - LambdaSol) - Mm));	/* sec 61 #7 */
	Ac = 0.1858 * sin(dtor(Msol));				/* sec 61 #8 */
	A3 = 0.37 * sin(dtor(Msol));
	Mmprime = Mm + Ev - Ac - A3;				/* sec 61 #9 */
	Ec = 6.2886 * sin(dtor(Mmprime));			/* sec 61 #10 */
	A4 = 0.214 * sin(dtor(2 * Mmprime));			/* sec 61 #11 */
	lprime = l + Ev + Ec - Ac + A4;				/* sec 61 #12 */
	V = 0.6583 * sin(dtor(2 * (lprime - LambdaSol)));	/* sec 61 #13 */
	ldprime = lprime + V;					/* sec 61 #14 */
	D = ldprime - LambdaSol;				/* sec 63 #2 */
	return(50 * (1 - cos(dtor(D))));			/* sec 63 #3 */
}