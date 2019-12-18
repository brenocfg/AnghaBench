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
 int ANGLE (double,double) ; 
 int /*<<< orphan*/  DEBUG2 (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,int,int) ; 
 int FSECSPERDAY ; 
 int /*<<< orphan*/  HOUR (int) ; 
 int HOURSPERDAY ; 
 int /*<<< orphan*/  MIN (int) ; 
 int /*<<< orphan*/  SEC (int) ; 
 int SECSPERDAY ; 
 int /*<<< orphan*/  SHOUR (int) ; 
 scalar_t__ SIGN (double) ; 
 int /*<<< orphan*/  SMIN (int) ; 
 int /*<<< orphan*/  SSEC (int) ; 
 int** cumdaytab ; 
 size_t isleap (int) ; 
 int /*<<< orphan*/  sunpos (int,int,int,double,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double,double*,double*) ; 

void
fequinoxsolstice(int year, double UTCoffset, double *equinoxdays, double *solsticedays)
{
	double dec, prevdec, L;
	int h, d, prevangle, angle;
	int found = 0;

	double decleft, decright, decmiddle;
	int dial, s;

	int *cumdays;
	cumdays = cumdaytab[isleap(year)];

	/*
	 * Find the first equinox, somewhere in March:
	 * It happens when the returned value "dec" goes from
	 * [350 ... 360> -> [0 ... 10]
	 */
	for (d = 18; d < 31; d++) {
		/* printf("Comparing day %d to %d.\n", d, d+1); */
		sunpos(year, 3, d, UTCoffset, 0, 0, 0, 0.0, 0.0, &L, &decleft);
		sunpos(year, 3, d + 1, UTCoffset, 0, 0, 0, 0.0, 0.0,
		    &L, &decright);
		/* printf("Found %g and %g.\n", decleft, decright); */
		if (SIGN(decleft) == SIGN(decright))
			continue;

		dial = SECSPERDAY;
		s = SECSPERDAY / 2;
		while (s > 0) {
			/* printf("Obtaining %d (%02d:%02d)\n",
			    dial, SHOUR(dial), SMIN(dial)); */
			sunpos(year, 3, d, UTCoffset,
			    SHOUR(dial), SMIN(dial), SSEC(dial),
			    0.0, 0.0, &L, &decmiddle);
			/* printf("Found %g\n", decmiddle); */
			if (SIGN(decleft) == SIGN(decmiddle)) {
				decleft = decmiddle;
				dial += s;
			} else {
				decright = decmiddle;
				dial -= s;
			}
			/*
			 printf("New boundaries: %g - %g\n", decleft, decright);
			*/

			s /= 2;
		}
		equinoxdays[0] = 1 + cumdays[3] + d + (dial / FSECSPERDAY);
		break;
	}

	/* Find the second equinox, somewhere in September:
	 * It happens when the returned value "dec" goes from
	 * [10 ... 0] -> <360 ... 350]
	 */
	for (d = 18; d < 31; d++) {
		/* printf("Comparing day %d to %d.\n", d, d+1); */
		sunpos(year, 9, d, UTCoffset, 0, 0, 0, 0.0, 0.0, &L, &decleft);
		sunpos(year, 9, d + 1, UTCoffset, 0, 0, 0, 0.0, 0.0,
		    &L, &decright);
		/* printf("Found %g and %g.\n", decleft, decright); */
		if (SIGN(decleft) == SIGN(decright))
			continue;

		dial = SECSPERDAY;
		s = SECSPERDAY / 2;
		while (s > 0) {
			/* printf("Obtaining %d (%02d:%02d)\n",
			    dial, SHOUR(dial), SMIN(dial)); */
			sunpos(year, 9, d, UTCoffset,
			    SHOUR(dial), SMIN(dial), SSEC(dial),
			    0.0, 0.0, &L, &decmiddle);
			/* printf("Found %g\n", decmiddle); */
			if (SIGN(decleft) == SIGN(decmiddle)) {
				decleft = decmiddle;
				dial += s;
			} else {
				decright = decmiddle;
				dial -= s;
			}
			/*
			printf("New boundaries: %g - %g\n", decleft, decright);
			*/

			s /= 2;
		}
		equinoxdays[1] = 1 + cumdays[9] + d + (dial / FSECSPERDAY);
		break;
	}

	/*
	 * Find the first solstice, somewhere in June:
	 * It happens when the returned value "dec" peaks
	 * [40 ... 45] -> [45 ... 40]
	 */
	found = 0;
	prevdec = 0;
	prevangle = 1;
	for (d = 18; d < 31; d++) {
		for (h = 0; h < 4 * HOURSPERDAY; h++) {
			sunpos(year, 6, d, UTCoffset, HOUR(h), MIN(h), SEC(h),
			    0.0, 0.0, &L, &dec);
			angle = ANGLE(prevdec, dec);
			if (prevangle != angle) {
#ifdef NOTDEF
				DEBUG2(year, 6, d, HOUR(h), MIN(h),
				    prevdec, dec, prevangle, angle);
#endif
				solsticedays[0] = 1 + cumdays[6] + d +
				    ((h / 4.0) / 24.0);
				found = 1;
				break;
			}
			prevdec = dec;
			prevangle = angle;
		}
		if (found)
			break;
	}

	/*
	 * Find the second solstice, somewhere in December:
	 * It happens when the returned value "dec" peaks
	 * [315 ... 310] -> [310 ... 315]
	 */
	found = 0;
	prevdec = 360;
	prevangle = -1;
	for (d = 18; d < 31; d++) {
		for (h = 0; h < 4 * HOURSPERDAY; h++) {
			sunpos(year, 12, d, UTCoffset, HOUR(h), MIN(h), SEC(h),
			    0.0, 0.0, &L, &dec);
			angle = ANGLE(prevdec, dec);
			if (prevangle != angle) {
#ifdef NOTDEF
				DEBUG2(year, 12, d, HOUR(h), MIN(h),
				    prevdec, dec, prevangle, angle);
#endif
				solsticedays[1] = 1 + cumdays[12] + d +
				    ((h / 4.0) / 24.0);
				found = 1;
				break;
			}
			prevdec = dec;
			prevangle = angle;
		}
		if (found)
			break;
	}

	return;
}