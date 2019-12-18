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

__attribute__((used)) static int 
MT2032_SpurCheck(int f1, int f2, int spectrum_from, int spectrum_to)
{
	int             n1 = 1, n2, f;

	f1 = f1 / 1000;		/* scale to kHz to avoid 32bit overflows */
	f2 = f2 / 1000;
	spectrum_from /= 1000;
	spectrum_to /= 1000;

	do {
		n2 = -n1;
		f = n1 * (f1 - f2);
		do {
			n2--;
			f = f - f2;
			if ((f > spectrum_from) && (f < spectrum_to)) {
				return 1;
			}
		} while ((f > (f2 - spectrum_to)) || (n2 > -5));
		n1++;
	} while (n1 < 5);

	return 0;
}