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
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int GEOM_GETXML_RETRIES ; 
 scalar_t__ GEOM_GETXML_SLACK ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* reallocf (char*,scalar_t__) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ sysctl (int*,size_t,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlnametomib (char*,int*,size_t*) ; 

char *
geom_getxml(void)
{
	char *p;
	size_t l = 0;
	int mib[3];
	size_t sizep;
	int retries;

	sizep = sizeof(mib) / sizeof(*mib);
	if (sysctlnametomib("kern.geom.confxml", mib, &sizep) != 0)
		return (NULL);
	if (sysctl(mib, sizep, NULL, &l, NULL, 0) != 0)
		return (NULL);
	l += GEOM_GETXML_SLACK;

	for (retries = 0; retries < GEOM_GETXML_RETRIES; retries++) {
		p = malloc(l);
		if (p == NULL)
			return (NULL);
		if (sysctl(mib, sizep, p, &l, NULL, 0) == 0)
			return (reallocf(p, strlen(p) + 1));

		free(p);

		if (errno != ENOMEM)
			return (NULL);

		/*
		 * Our buffer wasn't big enough. Make it bigger and
		 * try again.
		 */
		l *= 2;
	}

	return (NULL);
}