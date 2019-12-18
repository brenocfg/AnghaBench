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
 scalar_t__ strncasecmp (char const*,char const*,int) ; 

__attribute__((used)) static int
ofw_bus_node_is_compatible_int(const char *compat, int len,
    const char *onecompat)
{
	int onelen, l, ret;

	onelen = strlen(onecompat);

	ret = 0;
	while (len > 0) {
		if (strlen(compat) == onelen &&
		    strncasecmp(compat, onecompat, onelen) == 0) {
			/* Found it. */
			ret = 1;
			break;
		}

		/* Slide to the next sub-string. */
		l = strlen(compat) + 1;
		compat += l;
		len -= l;
	}

	return (ret);
}