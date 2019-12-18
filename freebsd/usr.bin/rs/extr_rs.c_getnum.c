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
 int atoi (char*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 

__attribute__((used)) static char *
getnum(int *num, char *p, int strict)
{
	char *t = p;

	if (!isdigit((unsigned char)*++t)) {
		if (strict || *t == '-' || *t == '+')
			errx(1, "option %.1s requires an unsigned integer", p);
		*num = 0;
		return(p);
	}
	*num = atoi(t);
	while (*++t)
		if (!isdigit((unsigned char)*t))
			break;
	return(--t);
}