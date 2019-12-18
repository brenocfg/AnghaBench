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
struct regulator_range {int min_uvolt; int max_sel; int min_sel; int step_uvolt; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ERANGE ; 
 int /*<<< orphan*/  panic (char*) ; 
 int regulator_range_sel8_to_volt (struct regulator_range*,int,int,int*) ; 

int
regulator_range_volt_to_sel8(struct regulator_range *ranges, int nranges,
    int min_uvolt, int max_uvolt, uint8_t *out_sel)
{
	struct regulator_range *range;
	uint8_t sel;
	int uvolt;
	int rv, i;

	if (nranges == 0)
		panic("Voltage regulator have zero ranges\n");

	for (i = 0; i < nranges; i++) {
		range = ranges  + i;
		uvolt = range->min_uvolt +
		    (range->max_sel - range->min_sel) * range->step_uvolt;

		if ((min_uvolt > uvolt) ||
		    (max_uvolt < range->min_uvolt))
			continue;

		if (min_uvolt <= range->min_uvolt)
			min_uvolt = range->min_uvolt;

		/* if step == 0 -> fixed voltage range. */
		if (range->step_uvolt == 0)
			sel = 0;
		else
			sel = DIV_ROUND_UP(min_uvolt - range->min_uvolt,
			   range->step_uvolt);


		sel += range->min_sel;

		break;
	}

	if (i >= nranges)
		return (ERANGE);

	/* Verify new settings. */
	rv = regulator_range_sel8_to_volt(ranges, nranges, sel, &uvolt);
	if (rv != 0)
		return (rv);
	if ((uvolt < min_uvolt) || (uvolt > max_uvolt))
		return (ERANGE);

	*out_sel = sel;
	return (0);
}