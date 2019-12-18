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
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char const*) ; 
 double strtod (char const*,char**) ; 

__attribute__((used)) static double
e_atof(const char *num)
{
	char *endp;
	double dbl;

	errno = 0;
	dbl = strtod(num, &endp);

	if (errno == ERANGE)
		/* under or overflow */
		err(2, "%s", num);
	else if (*endp != '\0')
		/* "junk" left in number */
		errx(2, "invalid floating point argument: %s", num);

	/* zero shall have no sign */
	if (dbl == -0.0)
		dbl = 0;
	return (dbl);
}