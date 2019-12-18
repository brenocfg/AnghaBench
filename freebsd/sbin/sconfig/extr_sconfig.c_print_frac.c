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
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void
print_frac (int leftalign, unsigned long numerator, unsigned long divider)
{
	int n;

	if (numerator < 1 || divider < 1) {
		printf (leftalign ? "/-   " : "    -");
		return;
	}
	n = (int) (0.5 + 1000.0 * numerator / divider);
	if (n < 1000) {
		printf (leftalign ? "/.%-3d" : " .%03d", n);
		return;
	}
	putchar (leftalign ? '/' : ' ');

	if      (n >= 1000000) n = (n+500) / 1000 * 1000;
	else if (n >= 100000)  n = (n+50)  / 100 * 100;
	else if (n >= 10000)   n = (n+5)   / 10 * 10;

	switch (n) {
	case 1000:    printf (".999"); return;
	case 10000:   n = 9990;   break;
	case 100000:  n = 99900;  break;
	case 1000000: n = 999000; break;
	}
	if (n < 10000)        printf ("%d.%d", n/1000, n/10%100);
	else if (n < 100000)  printf ("%d.%d", n/1000, n/100%10);
	else if (n < 1000000) printf ("%d.", n/1000);
	else                  printf ("%d", n/1000);
}