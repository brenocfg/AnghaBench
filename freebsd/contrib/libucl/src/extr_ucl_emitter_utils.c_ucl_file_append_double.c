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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBL_DIG ; 
 double const fabs (double) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,double,...) ; 

__attribute__((used)) static int
ucl_file_append_double (double val, void *ud)
{
	FILE *fp = ud;
	const double delta = 0.0000001;

	if (val == (double)(int)val) {
		fprintf (fp, "%.1lf", val);
	}
	else if (fabs (val - (double)(int)val) < delta) {
		/* Write at maximum precision */
		fprintf (fp, "%.*lg", DBL_DIG, val);
	}
	else {
		fprintf (fp, "%lf", val);
	}

	return 0;
}