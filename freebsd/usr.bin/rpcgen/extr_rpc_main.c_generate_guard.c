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
 char* extendfile (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ islower (char) ; 
 scalar_t__ isupper (char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 void* strrchr (char const*,char) ; 
 char toupper (char) ; 
 char* xstrdup (char const*) ; 

char *
generate_guard(const char *pathname)
{
	const char *filename;
	char *guard, *tmp, *stopat;

	filename = strrchr(pathname, '/');  /* find last component */
	filename = ((filename == NULL) ? pathname : filename+1);
	guard = xstrdup(filename);
	stopat = strrchr(guard, '.');

	/*
	 * Convert to a valid C macro name and make it upper case.
	 * Map macro unfriendly characterss to '_'.
	 */
	for (tmp = guard; *tmp != '\000'; ++tmp) {
		if (islower(*tmp))
			*tmp = toupper(*tmp);
		else if (isupper(*tmp) || *tmp == '_')
			/* OK for C */;
		else if (tmp == guard)
			*tmp = '_';
		else if (isdigit(*tmp))
			/* OK for all but first character */;
		else if (tmp == stopat) {
			*tmp = '\0';
			break;
		} else
			*tmp = '_';
	}
	/*
	 * Can't have a '_' in front, because it'll end up being "__".
	 * "__" macros shoudln't be used. So, remove all of the
	 * '_' characters from the front.
	 */
	if (*guard == '_') {
		for (tmp = guard; *tmp == '_'; ++tmp)
			;
		strcpy(guard, tmp);
	}
	tmp = guard;
	guard = extendfile(guard, "_H_RPCGEN");
	free(tmp);
	return (guard);
}