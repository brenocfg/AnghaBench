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
 scalar_t__* boolfalse ; 
 scalar_t__* booltrue ; 
 scalar_t__ strcmp (char const*,scalar_t__) ; 
 char* unquote (char const*) ; 

int
boolean_val(char const * str, int dflt)
{
	if ((str = unquote(str)) != NULL) {
		int             i;

		for (i = 0; booltrue[i]; i++)
			if (strcmp(str, booltrue[i]) == 0)
				return 1;
		for (i = 0; boolfalse[i]; i++)
			if (strcmp(str, boolfalse[i]) == 0)
				return 0;
	}
	return dflt;
}