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
 char* MOUNT_META_OPTION_CURRENT ; 
 char* MOUNT_META_OPTION_FSTAB ; 
 char* catopt (char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 char* flags2opts (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  remopt (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* strdup (char*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 char* strsep (char**,char*) ; 

char *
update_options(char *opts, char *fstab, int curflags)
{
	char *o, *p;
	char *cur;
	char *expopt, *newopt, *tmpopt;

	if (opts == NULL)
		return (strdup(""));

	/* remove meta options from list */
	remopt(fstab, MOUNT_META_OPTION_FSTAB);
	remopt(fstab, MOUNT_META_OPTION_CURRENT);
	cur = flags2opts(curflags);

	/*
	 * Expand all meta-options passed to us first.
	 */
	expopt = NULL;
	for (p = opts; (o = strsep(&p, ",")) != NULL;) {
		if (strcmp(MOUNT_META_OPTION_FSTAB, o) == 0)
			expopt = catopt(expopt, fstab);
		else if (strcmp(MOUNT_META_OPTION_CURRENT, o) == 0)
			expopt = catopt(expopt, cur);
		else
			expopt = catopt(expopt, o);
	}
	free(cur);
	free(opts);

	/*
	 * Remove previous contradictory arguments. Given option "foo" we
	 * remove all the "nofoo" options. Given "nofoo" we remove "nonofoo"
	 * and "foo" - so we can deal with possible options like "notice".
	 */
	newopt = NULL;
	for (p = expopt; (o = strsep(&p, ",")) != NULL;) {
		if ((tmpopt = malloc( strlen(o) + 2 + 1 )) == NULL)
			errx(1, "malloc failed");

		strcpy(tmpopt, "no");
		strcat(tmpopt, o);
		remopt(newopt, tmpopt);
		free(tmpopt);

		if (strncmp("no", o, 2) == 0)
			remopt(newopt, o+2);

		newopt = catopt(newopt, o);
	}
	free(expopt);

	return (newopt);
}