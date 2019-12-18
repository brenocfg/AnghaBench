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
 int /*<<< orphan*/  AUDIT_CONTROL_FILE ; 
 int /*<<< orphan*/  AU_LINE_MAX ; 
 int /*<<< orphan*/  delim ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fp ; 
 char* linestr ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strtok_r (char*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static int
getstrfromtype_locked(const char *name, char **str)
{
	char *type, *nl;
	char *tokptr;
	char *last;

	*str = NULL;

	if ((fp == NULL) && ((fp = fopen(AUDIT_CONTROL_FILE, "r")) == NULL))
		return (-1); /* Error */

	while (1) {
		if (fgets(linestr, AU_LINE_MAX, fp) == NULL) {
			if (ferror(fp))
				return (-1);
			return (0);	/* EOF */
		}

		if (linestr[0] == '#')
			continue;

		/* Remove trailing new line character and white space. */
		nl = strchr(linestr, '\0') - 1;
		while (nl >= linestr && ('\n' == *nl || ' ' == *nl ||
			'\t' == *nl)) {
			*nl = '\0';
			nl--;
		}

		tokptr = linestr;
		if ((type = strtok_r(tokptr, delim, &last)) != NULL) {
			if (strcmp(name, type) == 0) {
				/* Found matching name. */
				*str = last;
				return (0); /* Success */
			}
		}
	}
}