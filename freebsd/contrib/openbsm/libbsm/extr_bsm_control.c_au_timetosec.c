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
typedef  int /*<<< orphan*/  u_long ;
typedef  int time_t ;

/* Variables and functions */

__attribute__((used)) static int
au_timetosec(time_t *seconds, u_long value, char mult)
{
	if (NULL == seconds)
		return (-1);

	switch(mult) {
	case 's':
		/* seconds */
		*seconds = (time_t)value;
		break;

	case 'h':
		/* hours */
		*seconds = (time_t)value * 60 * 60;
		break;

	case 'd':
		/* days */
		*seconds = (time_t)value * 60 * 60 * 24;
		break;

	case 'y':
		/* years.  Add a day for each 4th (leap) year. */
		*seconds = (time_t)value * 60 * 60 * 24 * 364 +
		    ((time_t)value / 4) * 60 * 60 * 24;
		break;

	default:
		return (-1);
	}
	return (0);
}