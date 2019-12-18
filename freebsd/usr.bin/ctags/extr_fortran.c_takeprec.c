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
 scalar_t__ isdigit (char) ; 
 scalar_t__ isspace (char) ; 
 char* lbp ; 

__attribute__((used)) static void
takeprec(void)
{
	for (; isspace(*lbp); ++lbp)
		continue;
	if (*lbp == '*') {
		for (++lbp; isspace(*lbp); ++lbp)
			continue;
		if (!isdigit(*lbp))
			--lbp;			/* force failure */
		else
			while (isdigit(*++lbp))
				continue;
	}
}