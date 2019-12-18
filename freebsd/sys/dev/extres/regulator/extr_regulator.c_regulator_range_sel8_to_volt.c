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
typedef  int uint8_t ;
struct regulator_range {int min_sel; int max_sel; int min_uvolt; int step_uvolt; } ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  panic (char*) ; 

int
regulator_range_sel8_to_volt(struct regulator_range *ranges, int nranges,
   uint8_t sel, int *volt)
{
	struct regulator_range *range;
	int i;

	if (nranges == 0)
		panic("Voltage regulator have zero ranges\n");

	for (i = 0; i < nranges ; i++) {
		range = ranges  + i;

		if (!(sel >= range->min_sel &&
		      sel <= range->max_sel))
			continue;

		sel -= range->min_sel;

		*volt = range->min_uvolt + sel * range->step_uvolt;
		return (0);
	}

	return (ERANGE);
}