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
 int NO ; 
 int YES ; 
 char* lbp ; 

int
cicmp(const char *cp)
{
	int	len;
	char	*bp;

	for (len = 0, bp = lbp; *cp && (*cp &~ ' ') == (*bp++ &~ ' ');
	    ++cp, ++len)
		continue;
	if (!*cp) {
		lbp += len;
		return (YES);
	}
	return (NO);
}