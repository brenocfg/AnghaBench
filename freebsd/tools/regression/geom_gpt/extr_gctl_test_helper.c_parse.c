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
 int EINVAL ; 
 int ENOMEM ; 
 int PATH_MAX ; 
 char* calloc (int,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
parse(char *arg, char **param, char **value, int *len)
{
	char *e, *colon, *equal;

	if (*arg == '\0')
		return (EINVAL);

	colon = strchr(arg, ':');
	equal = strchr(arg, '=');
	if (colon == NULL && equal == NULL)
		return (EINVAL);
	if (colon == arg || equal == arg)
		return (EINVAL);
	if (colon != NULL && equal != NULL && equal < colon)
		return (EINVAL);

	if (colon != NULL)
		*colon++ = '\0';
	if (equal != NULL)
		*equal++ = '\0';

	*param = arg;
	if (colon != NULL) {
		/* Length specification. This parameter is RW. */
		if (*colon == '\0')
			return (EINVAL);
		*len = strtol(colon, &e, 0);
		if (*e != '\0')
			return (EINVAL);
		if (*len <= 0 || *len > PATH_MAX)
			return (EINVAL);
		*value = calloc(*len, sizeof(char));
		if (*value == NULL)
			return (ENOMEM);
		if (equal != NULL) {
			if (strlen(equal) >= PATH_MAX)
				return (ENOMEM);
			strcpy(*value, equal);
		}
	} else {
		/* This parameter is RO. */
		*len = -1;
		if (*equal == '\0')
			return (EINVAL);
		*value = equal;
	}

	return (0);
}