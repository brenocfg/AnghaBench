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
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  ng_ID_t ;

/* Variables and functions */
 scalar_t__ ULONG_MAX ; 
 int /*<<< orphan*/  isxdigit (char const) ; 
 int strlen (char const*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static ng_ID_t
ng_decodeidname(const char *name)
{
	const int len = strlen(name);
	char *eptr;
	u_long val;

	/* Check for proper length, brackets, no leading junk */
	if ((len < 3) || (name[0] != '[') || (name[len - 1] != ']') ||
	    (!isxdigit(name[1])))
		return ((ng_ID_t)0);

	/* Decode number */
	val = strtoul(name + 1, &eptr, 16);
	if ((eptr - name != len - 1) || (val == ULONG_MAX) || (val == 0))
		return ((ng_ID_t)0);

	return ((ng_ID_t)val);
}