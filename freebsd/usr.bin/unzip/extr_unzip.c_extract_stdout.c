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
 int /*<<< orphan*/  STDOUT_FILENO ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  accept_pathname (char*) ; 
 int /*<<< orphan*/  archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_pathname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_read_data_skip (struct archive*) ; 
 scalar_t__ c_opt ; 
 int /*<<< orphan*/  extract2fd (struct archive*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  info (char*,char*) ; 
 char* pathdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warningx (char*,char*) ; 

__attribute__((used)) static void
extract_stdout(struct archive *a, struct archive_entry *e)
{
	char *pathname;
	mode_t filetype;

	pathname = pathdup(archive_entry_pathname(e));
	filetype = archive_entry_filetype(e);

	/* I don't think this can happen in a zipfile.. */
	if (!S_ISDIR(filetype) && !S_ISREG(filetype) && !S_ISLNK(filetype)) {
		warningx("skipping non-regular entry '%s'", pathname);
		ac(archive_read_data_skip(a));
		free(pathname);
		return;
	}

	/* skip directories in -j case */
	if (S_ISDIR(filetype)) {
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

	if (c_opt)
		info("x %s\n", pathname);

	(void)extract2fd(a, pathname, STDOUT_FILENO);

	free(pathname);
}