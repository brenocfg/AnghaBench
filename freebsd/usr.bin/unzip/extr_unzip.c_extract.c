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
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accept_pathname (char*) ; 
 int /*<<< orphan*/  archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 int /*<<< orphan*/  d_arg ; 
 int /*<<< orphan*/  extract_dir (struct archive*,struct archive_entry*,char*) ; 
 int /*<<< orphan*/  extract_file (struct archive*,struct archive_entry*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ j_opt ; 
 int /*<<< orphan*/  make_parent (char*) ; 
 char* pathcat (int /*<<< orphan*/ ,char*) ; 
 char* pathdup (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  warningx (char*,char*) ; 

__attribute__((used)) static void
extract(struct archive *a, struct archive_entry *e)
{
	char *pathname, *realpathname;
	mode_t filetype;
	char *p, *q;

	pathname = pathdup(archive_entry_pathname(e));
	filetype = archive_entry_filetype(e);

	/* sanity checks */
	if (pathname[0] == '/' ||
	    strncmp(pathname, "../", 3) == 0 ||
	    strstr(pathname, "/../") != NULL) {
		warningx("skipping insecure entry '%s'", pathname);
		ac(archive_read_data_skip(a));
		free(pathname);
		return;
	}

	/* I don't think this can happen in a zipfile.. */
	if (!S_ISDIR(filetype) && !S_ISREG(filetype) && !S_ISLNK(filetype)) {
		warningx("skipping non-regular entry '%s'", pathname);
		ac(archive_read_data_skip(a));
		free(pathname);
		return;
	}

	/* skip directories in -j case */
	if (S_ISDIR(filetype) && j_opt) {
		ac(archive_read_data_skip(a));
		free(pathname);
		return;
	}

	/* apply include / exclude patterns */
	if (!accept_pathname(pathname)) {
		ac(archive_read_data_skip(a));
		free(pathname);
		return;
	}

	/* apply -j and -d */
	if (j_opt) {
		for (p = q = pathname; *p; ++p)
			if (*p == '/')
				q = p + 1;
		realpathname = pathcat(d_arg, q);
	} else {
		realpathname = pathcat(d_arg, pathname);
	}

	/* ensure that parent directory exists */
	make_parent(realpathname);

	if (S_ISDIR(filetype))
		extract_dir(a, e, realpathname);
	else
		extract_file(a, e, &realpathname);

	free(realpathname);
	free(pathname);
}