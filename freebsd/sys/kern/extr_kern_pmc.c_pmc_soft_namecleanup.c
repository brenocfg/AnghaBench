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
 int /*<<< orphan*/  toupper (char) ; 

__attribute__((used)) static void
pmc_soft_namecleanup(char *name)
{
	char *p, *q;

	p = q = name;

	for ( ; *p == '_' ; p++)
		;
	for ( ; *p ; p++) {
		if (*p == '_' && (*(p + 1) == '_' || *(p + 1) == '\0'))
			continue;
		else
			*q++ = toupper(*p);
	}
	*q = '\0';
}