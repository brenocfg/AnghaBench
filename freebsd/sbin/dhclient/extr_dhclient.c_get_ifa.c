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
struct sockaddr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADVANCE (char*,struct sockaddr*) ; 
 unsigned int RTA_IFA ; 

struct sockaddr *
get_ifa(char *cp, int n)
{
	struct sockaddr *sa;
	unsigned i;

	if (n == 0)
		return (NULL);
	for (i = 1; i; i <<= 1)
		if (i & n) {
			sa = (struct sockaddr *)cp;
			if (i == RTA_IFA)
				return (sa);
			ADVANCE(cp, sa);
		}

	return (NULL);
}