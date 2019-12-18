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
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 char* getsval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gettemp () ; 
 int /*<<< orphan*/  setfval (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *sindex(Node **a, int nnn)		/* index(a[0], a[1]) */
{
	Cell *x, *y, *z;
	char *s1, *s2, *p1, *p2, *q;
	Awkfloat v = 0.0;

	x = execute(a[0]);
	s1 = getsval(x);
	y = execute(a[1]);
	s2 = getsval(y);

	z = gettemp();
	for (p1 = s1; *p1 != '\0'; p1++) {
		for (q=p1, p2=s2; *p2 != '\0' && *q == *p2; q++, p2++)
			;
		if (*p2 == '\0') {
			v = (Awkfloat) (p1 - s1 + 1);	/* origin 1 */
			break;
		}
	}
	tempfree(x);
	tempfree(y);
	setfval(z, v);
	return(z);
}