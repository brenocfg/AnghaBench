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
 char* default_bootfiles ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 char* malloc (size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
getbootfile(int try)
{
	static char *name = NULL;
	const char	*spec, *ep;
	size_t	len;

	/* we use dynamic storage */
	if (name != NULL) {
		free(name);
		name = NULL;
	}

	/*
	 * Try $bootfile, then try our builtin default
	 */
	if ((spec = getenv("bootfile")) == NULL)
		spec = default_bootfiles;

	while ((try > 0) && (spec != NULL)) {
		spec = strchr(spec, ';');
		if (spec)
			spec++;	/* skip over the leading ';' */
		try--;
	}
	if (spec != NULL) {
		if ((ep = strchr(spec, ';')) != NULL) {
			len = ep - spec;
		} else {
			len = strlen(spec);
		}
		name = malloc(len + 1);
		strncpy(name, spec, len);
		name[len] = 0;
	}
	if (name && name[0] == 0) {
		free(name);
		name = NULL;
	}
	return(name);
}