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
 scalar_t__ toupper (int) ; 

__attribute__((used)) static int
pmc_match_event_name(const char *name, const char *canonicalname)
{
	int cc, nc;
	const unsigned char *c, *n;

	c = (const unsigned char *) canonicalname;
	n = (const unsigned char *) name;

	for (; (nc = *n) && (cc = *c); n++, c++) {

		if ((nc == ' ' || nc == '_' || nc == '-' || nc == '.') &&
		    (cc == ' ' || cc == '_' || cc == '-' || cc == '.'))
			continue;

		if (toupper(nc) == toupper(cc))
			continue;


		return (0);
	}

	if (*n == '\0' && *c == '\0')
		return (1);

	return (0);
}