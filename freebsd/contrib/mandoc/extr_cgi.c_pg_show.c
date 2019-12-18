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
struct req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FOCUS_NONE ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* mandoc_strndup (char const*,int) ; 
 int /*<<< orphan*/  pg_error_badrequest (char*) ; 
 int /*<<< orphan*/  pg_error_internal () ; 
 int /*<<< orphan*/  resp_begin_html (int,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  resp_end_html () ; 
 int /*<<< orphan*/  resp_searchform (struct req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resp_show (struct req*,char const*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  validate_filename (char const*) ; 
 int /*<<< orphan*/  validate_manpath (struct req*,char*) ; 
 int /*<<< orphan*/  warn (char*,char*) ; 

__attribute__((used)) static void
pg_show(struct req *req, const char *fullpath)
{
	char		*manpath;
	const char	*file;

	if ((file = strchr(fullpath, '/')) == NULL) {
		pg_error_badrequest(
		    "You did not specify a page to show.");
		return;
	}
	manpath = mandoc_strndup(fullpath, file - fullpath);
	file++;

	if ( ! validate_manpath(req, manpath)) {
		pg_error_badrequest(
		    "You specified an invalid manpath.");
		free(manpath);
		return;
	}

	/*
	 * Begin by chdir()ing into the manpath.
	 * This way we can pick up the database files, which are
	 * relative to the manpath root.
	 */

	if (chdir(manpath) == -1) {
		warn("chdir %s", manpath);
		pg_error_internal();
		free(manpath);
		return;
	}
	free(manpath);

	if ( ! validate_filename(file)) {
		pg_error_badrequest(
		    "You specified an invalid manual file.");
		return;
	}

	resp_begin_html(200, NULL, file);
	resp_searchform(req, FOCUS_NONE);
	resp_show(req, file);
	resp_end_html();
}