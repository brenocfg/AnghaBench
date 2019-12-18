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
struct dataset {int n; int* points; } ;

/* Variables and functions */

__attribute__((used)) static double
Median(const struct dataset *ds)
{
	const unsigned m = ds->n / 2;

	if ((ds->n % 2) == 0)
		return ((ds->points[m] + (ds->points[m - 1])) / 2);
	return (ds->points[m]);
}