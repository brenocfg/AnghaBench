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
 int HOUR (int) ; 
 int HOURSPERDAY ; 
 int MIN (int) ; 
 int /*<<< orphan*/  SEC (int) ; 
 int** cumdaytab ; 
 size_t isleap (int) ; 
 int** monthdaytab ; 
 int /*<<< orphan*/  printf (char*,int,int,int,int,int,int,double) ; 
 int /*<<< orphan*/  sunpos (int,int,int,int,int,int,int /*<<< orphan*/ ,double,double,double*,double*) ; 

int
calculatesunlongitude30(int year, int degreeGMToffset, int *ichinesemonths)
{
	int m, d, h;
	double dec;
	double curL, prevL;
	int *pichinesemonths, *monthdays, *cumdays, i;
	int firstmonth330 = -1;

	cumdays = cumdaytab[isleap(year)];
	monthdays = monthdaytab[isleap(year)];
	pichinesemonths = ichinesemonths;

	h = 0;
	sunpos(year - 1, 12, 31,
	    -24 * (degreeGMToffset / 360.0),
	    HOUR(h), MIN(h), SEC(h), 0.0, 0.0, &prevL, &dec);

	for (m = 1; m <= 12; m++) {
		for (d = 1; d <= monthdays[m]; d++) {
			for (h = 0; h < 4 * HOURSPERDAY; h++) {
				sunpos(year, m, d,
				    -24 * (degreeGMToffset / 360.0),
				    HOUR(h), MIN(h), SEC(h),
				    0.0, 0.0, &curL, &dec);
				if (curL < 180 && prevL > 180) {
					*pichinesemonths = cumdays[m] + d;
#ifdef DEBUG
printf("%04d-%02d-%02d %02d:%02d - %d %g\n",
    year, m, d, HOUR(h), MIN(h), *pichinesemonths, curL);
#endif
					    pichinesemonths++;
				} else {
					for (i = 0; i <= 360; i += 30)
						if (curL > i && prevL < i) {
							*pichinesemonths =
							    cumdays[m] + d;
#ifdef DEBUG
printf("%04d-%02d-%02d %02d:%02d - %d %g\n",
    year, m, d, HOUR(h), MIN(h), *pichinesemonths, curL);
#endif
							if (i == 330)
								firstmonth330 = *pichinesemonths;
							pichinesemonths++;
						}
				}
				prevL = curL;
			}
		}
	}
	*pichinesemonths = -1;
	return (firstmonth330);
}