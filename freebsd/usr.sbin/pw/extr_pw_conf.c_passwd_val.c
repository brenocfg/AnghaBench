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
 int P_NO ; 
 int P_NONE ; 
 int P_RANDOM ; 
 int P_YES ; 
 char** boolfalse ; 
 char** booltrue ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* unquote (char const*) ; 

int
passwd_val(char const * str, int dflt)
{
	if ((str = unquote(str)) != NULL) {
		int             i;

		for (i = 0; booltrue[i]; i++)
			if (strcmp(str, booltrue[i]) == 0)
				return P_YES;
		for (i = 0; boolfalse[i]; i++)
			if (strcmp(str, boolfalse[i]) == 0)
				return P_NO;

		/*
		 * Special cases for defaultpassword
		 */
		if (strcmp(str, "random") == 0)
			return P_RANDOM;
		if (strcmp(str, "none") == 0)
			return P_NONE;

		errx(1, "Invalid value for default password");
	}
	return dflt;
}