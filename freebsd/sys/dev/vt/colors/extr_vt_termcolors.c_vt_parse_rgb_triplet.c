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
 int strlen (char const*) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
vt_parse_rgb_triplet(const char *rgb, unsigned char *r,
    unsigned char *g, unsigned char *b)
{
	unsigned long v;
	const char *ptr;
	char *endptr;

	ptr = rgb;

	/* Handle #rrggbb case */
	if (*ptr == '#') {
		if (strlen(ptr) != 7)
			return (-1);
		v = strtoul(ptr + 1, &endptr, 16);
		if (*endptr != '\0')
			return (-1);

		*r = (v >> 16) & 0xff;
		*g = (v >>  8) & 0xff;
		*b = v & 0xff;

		return (0);
	}

	/* "r, g, b" case */
	v = strtoul(ptr, &endptr, 10);
	if (ptr == endptr)
		return (-1);
	if (v > 255)
		return (-1);
	*r = v & 0xff;
	ptr = endptr;

	/* skip separator */
	while (*ptr == ',' || *ptr == ' ')
		ptr++;

	v = strtoul(ptr, &endptr, 10);
	if (ptr == endptr)
		return (-1);
	if (v > 255)
		return (-1);
	*g = v & 0xff;
	ptr = endptr;

	/* skip separator */
	while (*ptr == ',' || *ptr == ' ')
		ptr++;

	v = strtoul(ptr, &endptr, 10);
	if (ptr == endptr)
		return (-1);
	if (v > 255)
		return (-1);
	*b = v & 0xff;
	ptr = endptr;

	/* skip trailing spaces */
	while (*ptr == ' ')
		ptr++;

	/* unexpected characters at the end of the string */
	if (*ptr != 0)
		return (-1);

	return (0);
}