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
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ bcmp (char*,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,char*,char*) ; 

int
cvtatos(uint64_t period, char *units, uint64_t *seconds)
{

	if (bcmp(units, "second", 6) == 0)
		*seconds = period;
	else if (bcmp(units, "minute", 6) == 0)
		*seconds = period * 60;
	else if (bcmp(units, "hour", 4) == 0)
		*seconds = period * 60 * 60;
	else if (bcmp(units, "day", 3) == 0)
		*seconds = period * 24 * 60 * 60;
	else {
		warnx("%s: bad units, specify %s\n", units,
		    "days, hours, minutes, or seconds");
		return (0);
	}
	return (1);
}