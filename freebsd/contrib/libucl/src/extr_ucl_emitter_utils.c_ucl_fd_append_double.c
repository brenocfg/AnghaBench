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
typedef  int /*<<< orphan*/  nbuf ;

/* Variables and functions */
 int /*<<< orphan*/  DBL_DIG ; 
 double const fabs (double) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,double,...) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ucl_fd_append_double (double val, void *ud)
{
	int fd = *(int *)ud;
	const double delta = 0.0000001;
	char nbuf[64];

	if (val == (double)(int)val) {
		snprintf (nbuf, sizeof (nbuf), "%.1lf", val);
	}
	else if (fabs (val - (double)(int)val) < delta) {
		/* Write at maximum precision */
		snprintf (nbuf, sizeof (nbuf), "%.*lg", DBL_DIG, val);
	}
	else {
		snprintf (nbuf, sizeof (nbuf), "%lf", val);
	}

	return write (fd, nbuf, strlen (nbuf));
}