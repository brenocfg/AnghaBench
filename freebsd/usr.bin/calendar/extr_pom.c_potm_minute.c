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
 double FSECSPERDAY ; 
 double SECSPERDAY ; 
 scalar_t__ floor (double) ; 
 double potm (double) ; 

__attribute__((used)) static double
potm_minute(double onday, int olddir) {
	double period = FSECSPERDAY / 2.0;
	double p1, p2;
	double before, after;
	int newdir;

//	printf("---> days:%g olddir:%d\n", days, olddir);

	p1 = onday + (period / SECSPERDAY);
	period /= 2;

	while (period > 30) {	/* half a minute */
//		printf("period:%g - p1:%g - ", period, p1);
		p2 = p1 + (2.0 / SECSPERDAY);
		before = potm(p1);
		after = potm(p2);
//		printf("before:%10.10g - after:%10.10g\n", before, after);
		newdir = before < after ? -1 : +1;
		if (olddir != newdir)
			p1 += (period / SECSPERDAY);
		else
			p1 -= (period / SECSPERDAY);
		period /= 2;
//		printf("newdir:%d - p1:%10.10f - period:%g\n",
//		    newdir, p1, period);
	}
	p1 -= floor(p1);
	//exit(0);
	return (p1);
}