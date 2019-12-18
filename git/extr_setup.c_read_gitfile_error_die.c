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
 int /*<<< orphan*/  BUG (char*) ; 
#define  READ_GITFILE_ERR_INVALID_FORMAT 135 
#define  READ_GITFILE_ERR_NOT_A_FILE 134 
#define  READ_GITFILE_ERR_NOT_A_REPO 133 
#define  READ_GITFILE_ERR_NO_PATH 132 
#define  READ_GITFILE_ERR_OPEN_FAILED 131 
#define  READ_GITFILE_ERR_READ_FAILED 130 
#define  READ_GITFILE_ERR_STAT_FAILED 129 
#define  READ_GITFILE_ERR_TOO_LARGE 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,char const*) ; 

void read_gitfile_error_die(int error_code, const char *path, const char *dir)
{
	switch (error_code) {
	case READ_GITFILE_ERR_STAT_FAILED:
	case READ_GITFILE_ERR_NOT_A_FILE:
		/* non-fatal; follow return path */
		break;
	case READ_GITFILE_ERR_OPEN_FAILED:
		die_errno(_("error opening '%s'"), path);
	case READ_GITFILE_ERR_TOO_LARGE:
		die(_("too large to be a .git file: '%s'"), path);
	case READ_GITFILE_ERR_READ_FAILED:
		die(_("error reading %s"), path);
	case READ_GITFILE_ERR_INVALID_FORMAT:
		die(_("invalid gitfile format: %s"), path);
	case READ_GITFILE_ERR_NO_PATH:
		die(_("no path in gitfile: %s"), path);
	case READ_GITFILE_ERR_NOT_A_REPO:
		die(_("not a git repository: %s"), dir);
	default:
		BUG("unknown error code");
	}
}