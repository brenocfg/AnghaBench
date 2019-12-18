#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PLAN ;

/* Variables and functions */
 int /*<<< orphan*/  F_EQUAL ; 
 int /*<<< orphan*/  F_GREATER ; 
 int /*<<< orphan*/  F_LESSTHAN ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char*) ; 
 long long strtoq (char*,char**,int) ; 

__attribute__((used)) static long long
find_parsenum(PLAN *plan, const char *option, char *vp, char *endch)
{
	long long value;
	char *endchar, *str;	/* Pointer to character ending conversion. */

	/* Determine comparison from leading + or -. */
	str = vp;
	switch (*str) {
	case '+':
		++str;
		plan->flags |= F_GREATER;
		break;
	case '-':
		++str;
		plan->flags |= F_LESSTHAN;
		break;
	default:
		plan->flags |= F_EQUAL;
		break;
	}

	/*
	 * Convert the string with strtoq().  Note, if strtoq() returns zero
	 * and endchar points to the beginning of the string we know we have
	 * a syntax error.
	 */
	value = strtoq(str, &endchar, 10);
	if (value == 0 && endchar == str)
		errx(1, "%s: %s: illegal numeric value", option, vp);
	if (endchar[0] && endch == NULL)
		errx(1, "%s: %s: illegal trailing character", option, vp);
	if (endch)
		*endch = endchar[0];
	return value;
}