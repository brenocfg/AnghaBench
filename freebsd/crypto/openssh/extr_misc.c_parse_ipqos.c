#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u_int ;
struct TYPE_2__ {int value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 TYPE_1__* ipqos ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ *) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int
parse_ipqos(const char *cp)
{
	u_int i;
	char *ep;
	long val;

	if (cp == NULL)
		return -1;
	for (i = 0; ipqos[i].name != NULL; i++) {
		if (strcasecmp(cp, ipqos[i].name) == 0)
			return ipqos[i].value;
	}
	/* Try parsing as an integer */
	val = strtol(cp, &ep, 0);
	if (*cp == '\0' || *ep != '\0' || val < 0 || val > 255)
		return -1;
	return val;
}