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
 int MAX (int,int) ; 
 int decimal_places (char*) ; 
 int /*<<< orphan*/  decimal_point ; 
 char* default_format ; 
 double floor (double) ; 
 int sprintf (char*,char*,char,...) ; 
 scalar_t__ strchr (char*,char) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *
generate_format(double first, double incr, double last, int equalize, char pad)
{
	static char buf[256];
	char cc = '\0';
	int precision, width1, width2, places;

	if (equalize == 0)
		return (default_format);

	/* figure out "last" value printed */
	if (first > last)
		last = first - incr * floor((first - last) / incr);
	else
		last = first + incr * floor((last - first) / incr);

	sprintf(buf, "%g", incr);
	if (strchr(buf, 'e'))
		cc = 'e';
	precision = decimal_places(buf);

	width1 = sprintf(buf, "%g", first);
	if (strchr(buf, 'e'))
		cc = 'e';
	if ((places = decimal_places(buf)))
		width1 -= (places + strlen(decimal_point));

	precision = MAX(places, precision);

	width2 = sprintf(buf, "%g", last);
	if (strchr(buf, 'e'))
		cc = 'e';
	if ((places = decimal_places(buf)))
		width2 -= (places + strlen(decimal_point));

	if (precision) {
		sprintf(buf, "%%%c%d.%d%c", pad,
		    MAX(width1, width2) + (int) strlen(decimal_point) +
		    precision, precision, (cc) ? cc : 'f');
	} else {
		sprintf(buf, "%%%c%d%c", pad, MAX(width1, width2),
		    (cc) ? cc : 'g');
	}

	return (buf);
}