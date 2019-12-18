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

__attribute__((used)) static void julian_to_date(long jd, int *y, int *m, int *d)
{
    long L = jd + 68569;
    long n = (4 * L) / 146097;
    long i, j;

    L = L - (146097 * n + 3) / 4;
    i = (4000 * (L + 1)) / 1461001;
    L = L - (1461 * i) / 4 + 31;
    j = (80 * L) / 2447;
    *d = L - (2447 * j) / 80;
    L = j / 11;
    *m = j + 2 - (12 * L);
    *y = 100 * (n - 49) + i + L;
}