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
 scalar_t__ isspace (char) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
trimlr(char **buf)
{
	char *walk = *buf;
	char *last;

	while (isspace(*walk))
		walk++;
	if (*walk != '\0') {
		last = walk + strlen(walk) - 1;
		while (last > walk && isspace(*last))
			last--;
		*(last+1) = 0;
	}

	*buf = walk;
}