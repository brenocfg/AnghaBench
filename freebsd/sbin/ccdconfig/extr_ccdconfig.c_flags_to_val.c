#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fv_val; int /*<<< orphan*/ * fv_flag; } ;

/* Variables and functions */
 int CCDF_MIRROR ; 
 int CCDF_UNIFORM ; 
 scalar_t__ ERANGE ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 TYPE_1__* flagvaltab ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
flags_to_val(char *flags)
{
	char *cp, *tok;
	int i, tmp, val;

	errno = 0;	/* to check for ERANGE */
	val = (int)strtol(flags, &cp, 0);
	if ((errno != ERANGE) && (*cp == '\0')) {
		if (val & ~(CCDF_UNIFORM|CCDF_MIRROR))
			return (-1);
		return (val);
	}

	/* Check for values represented by strings. */
	if ((cp = strdup(flags)) == NULL)
		err(1, "no memory to parse flags");
	tmp = 0;
	for (tok = cp; (tok = strtok(tok, ",")) != NULL; tok = NULL) {
		for (i = 0; flagvaltab[i].fv_flag != NULL; ++i)
			if (strcmp(tok, flagvaltab[i].fv_flag) == 0)
				break;
		if (flagvaltab[i].fv_flag == NULL) {
			free(cp);
			return (-1);
		}
		tmp |= flagvaltab[i].fv_val;
	}

	/* If we get here, the string was ok. */
	free(cp);
	return (tmp);
}