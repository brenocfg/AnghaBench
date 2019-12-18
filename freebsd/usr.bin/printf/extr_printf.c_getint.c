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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ intmax_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
 int /*<<< orphan*/ * gargv ; 
 scalar_t__ getnum (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getint(int *ip)
{
	intmax_t val;
	uintmax_t uval;
	int rval;

	if (getnum(&val, &uval, 1))
		return (1);
	rval = 0;
	if (val < INT_MIN || val > INT_MAX) {
		warnx("%s: %s", *gargv, strerror(ERANGE));
		rval = 1;
	}
	*ip = (int)val;
	return (rval);
}