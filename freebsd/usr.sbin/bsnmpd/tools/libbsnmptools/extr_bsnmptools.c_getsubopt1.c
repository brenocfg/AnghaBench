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
typedef  int u_int ;

/* Variables and functions */
 int /*<<< orphan*/ * strchr (char const* const,char) ; 
 scalar_t__ strcmp (char*,char const* const) ; 

__attribute__((used)) static int
getsubopt1(char **arg, const char *const *options, char **valp, char **optp)
{
	static const char *const delim = ",\t ";
	u_int i;
	char *ptr;

	*optp = NULL;

	/* Skip leading junk. */
	for (ptr = *arg; *ptr != '\0'; ptr++)
		if (strchr(delim, *ptr) == NULL)
			break;
	if (*ptr == '\0') {
		*arg = ptr;
		return (-1);
	}
	*optp = ptr;

	/* Find the end of the option. */
	while (*++ptr != '\0')
		if (strchr(delim, *ptr) != NULL || *ptr == '=')
			break;

	if (*ptr != '\0') {
		if (*ptr == '=') {
			*ptr++ = '\0';
			*valp = ptr;
			while (*ptr != '\0' && strchr(delim, *ptr) == NULL)
				ptr++;
			if (*ptr != '\0')
				*ptr++ = '\0';
		} else
			*ptr++ = '\0';
	}

	*arg = ptr;

	for (i = 0; *options != NULL; options++, i++)
		if (strcmp(*optp, *options) == 0)
			return (i);
	return (-1);
}