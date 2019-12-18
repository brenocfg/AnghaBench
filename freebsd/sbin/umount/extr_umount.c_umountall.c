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
struct xvfsconf {int dummy; } ;
struct fstab {int /*<<< orphan*/  fs_file; int /*<<< orphan*/  fs_vfstype; int /*<<< orphan*/  fs_type; } ;

/* Variables and functions */
 char* FSTAB_RO ; 
 char* FSTAB_RQ ; 
 char* FSTAB_RW ; 
 scalar_t__ checkname (char*,char**) ; 
 scalar_t__ checkvfsname (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 struct fstab* getfsent () ; 
 int getvfsbyname (int /*<<< orphan*/ ,struct xvfsconf*) ; 
 char* malloc (size_t) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

int
umountall(char **typelist)
{
	struct xvfsconf vfc;
	struct fstab *fs;
	int rval;
	char *cp;
	static int firstcall = 1;

	if ((fs = getfsent()) != NULL)
		firstcall = 0;
	else if (firstcall)
		errx(1, "fstab reading failure");
	else
		return (0);
	do {
		/* Ignore the root. */
		if (strcmp(fs->fs_file, "/") == 0)
			continue;
		/*
		 * !!!
		 * Historic practice: ignore unknown FSTAB_* fields.
		 */
		if (strcmp(fs->fs_type, FSTAB_RW) &&
		    strcmp(fs->fs_type, FSTAB_RO) &&
		    strcmp(fs->fs_type, FSTAB_RQ))
			continue;
		/* Ignore unknown file system types. */
		if (getvfsbyname(fs->fs_vfstype, &vfc) == -1)
			continue;
		if (checkvfsname(fs->fs_vfstype, typelist))
			continue;

		/*
		 * We want to unmount the file systems in the reverse order
		 * that they were mounted.  So, we save off the file name
		 * in some allocated memory, and then call recursively.
		 */
		if ((cp = malloc((size_t)strlen(fs->fs_file) + 1)) == NULL)
			err(1, "malloc failed");
		(void)strcpy(cp, fs->fs_file);
		rval = umountall(typelist);
		rval = checkname(cp, typelist) || rval;
		free(cp);
		return (rval);
	} while ((fs = getfsent()) != NULL);
	return (0);
}