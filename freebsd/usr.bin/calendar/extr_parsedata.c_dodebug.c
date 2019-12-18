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
 int EastLongitude ; 
 int MAXMOONS ; 
 double UTCOffset ; 
 int /*<<< orphan*/  fequinoxsolstice (int,double,double*,double*) ; 
 char* floattoday (int,double) ; 
 int /*<<< orphan*/  fpom (int,double,double*,double*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int year1 ; 
 int year2 ; 

void
dodebug(char *what)
{
	int year;

	printf("UTCOffset: %g\n", UTCOffset);
	printf("eastlongitude: %d\n", EastLongitude);

	if (strcmp(what, "moon") == 0) {
		double ffullmoon[MAXMOONS], fnewmoon[MAXMOONS];
		int i;

		for (year = year1; year <= year2; year++) {
			fpom(year, UTCOffset, ffullmoon, fnewmoon);
			printf("Full moon %d:\t", year);
			for (i = 0; ffullmoon[i] >= 0; i++) {
				printf("%g (%s) ", ffullmoon[i],
				    floattoday(year, ffullmoon[i]));
			}
			printf("\nNew moon %d:\t", year);
			for (i = 0; fnewmoon[i] >= 0; i++) {
				printf("%g (%s) ", fnewmoon[i],
				    floattoday(year, fnewmoon[i]));
			}
			printf("\n");

		}

		return;
	}

	if (strcmp(what, "sun") == 0) {
		double equinoxdays[2], solsticedays[2];
		for (year = year1; year <= year2; year++) {
			printf("Sun in %d:\n", year);
			fequinoxsolstice(year, UTCOffset, equinoxdays,
			    solsticedays);
			printf("e[0] - %g (%s)\n",
			    equinoxdays[0],
			    floattoday(year, equinoxdays[0]));
			printf("e[1] - %g (%s)\n",
			    equinoxdays[1],
			    floattoday(year, equinoxdays[1]));
			printf("s[0] - %g (%s)\n",
			    solsticedays[0],
			    floattoday(year, solsticedays[0]));
			printf("s[1] - %g (%s)\n",
			    solsticedays[1],
			    floattoday(year, solsticedays[1]));
		}
		return;
	}
}