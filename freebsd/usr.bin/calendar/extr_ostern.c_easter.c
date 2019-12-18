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
 scalar_t__ isleap (int) ; 

int
easter(int year) /* 0 ... abcd, NOT since 1900 */
{
	int G,	/* Golden number - 1 */
	    C,	/* Century */
	    H,	/* 23 - epact % 30 */
	    I,	/* days from 21 March to Paschal full moon */
	    J,	/* weekday of full moon */
	    L;	/* days from 21 March to Sunday on of before full moon */

	G = year % 19;
	C = year / 100;
	H = (C - C / 4 - (8 * C + 13) / 25 + 19 * G + 15) % 30;
	I = H - (H / 28) * (1 - (H / 28) * (29 / (H + 1)) * ((21 - G) / 11));
	J = (year + year / 4 + I + 2 - C + C / 4) % 7;

	L = I - J;

	if (isleap(year))
		return 31 + 29 + 21 + L + 7;
	else
		return 31 + 28 + 21 + L + 7;
}