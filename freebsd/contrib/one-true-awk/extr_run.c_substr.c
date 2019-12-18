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

/* Variables and functions */
 int /*<<< orphan*/  dprintf (char*) ; 
 int /*<<< orphan*/ * execute (int /*<<< orphan*/ *) ; 
 scalar_t__ getfval (int /*<<< orphan*/ *) ; 
 char* getsval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gettemp () ; 
 int /*<<< orphan*/  setsval (int /*<<< orphan*/ *,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  tempfree (int /*<<< orphan*/ *) ; 

Cell *substr(Node **a, int nnn)		/* substr(a[0], a[1], a[2]) */
{
	int k, m, n;
	char *s;
	int temp;
	Cell *x, *y, *z = NULL;

	x = execute(a[0]);
	y = execute(a[1]);
	if (a[2] != NULL)
		z = execute(a[2]);
	s = getsval(x);
	k = strlen(s) + 1;
	if (k <= 1) {
		tempfree(x);
		tempfree(y);
		if (a[2] != NULL) {
			tempfree(z);
		}
		x = gettemp();
		setsval(x, "");
		return(x);
	}
	m = (int) getfval(y);
	if (m <= 0)
		m = 1;
	else if (m > k)
		m = k;
	tempfree(y);
	if (a[2] != NULL) {
		n = (int) getfval(z);
		tempfree(z);
	} else
		n = k - 1;
	if (n < 0)
		n = 0;
	else if (n > k - m)
		n = k - m;
	   dprintf( ("substr: m=%d, n=%d, s=%s\n", m, n, s) );
	y = gettemp();
	temp = s[n+m-1];	/* with thanks to John Linderman */
	s[n+m-1] = '\0';
	setsval(y, s + m - 1);
	s[n+m-1] = temp;
	tempfree(x);
	return(y);
}