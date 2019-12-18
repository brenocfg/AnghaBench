#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int ziplen; char* zipped; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ cflag ; 
 scalar_t__ dflag ; 
 scalar_t__ errno ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  handle_dir (char*) ; 
 int /*<<< orphan*/  handle_file (char*,struct stat*) ; 
 int /*<<< orphan*/  handle_stdin () ; 
 int /*<<< orphan*/  handle_stdout () ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  maybe_err (char*) ; 
 int /*<<< orphan*/  maybe_warn (char*,char*) ; 
 int /*<<< orphan*/  maybe_warnx (char*,char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ rflag ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int strlen (char*) ; 
 TYPE_1__* suffixes ; 

__attribute__((used)) static void
handle_pathname(char *path)
{
	char *opath = path, *s = NULL;
	ssize_t len;
	int slen;
	struct stat sb;

	/* check for stdout/stdin */
	if (path[0] == '-' && path[1] == '\0') {
		if (dflag)
			handle_stdin();
		else
			handle_stdout();
		return;
	}

retry:
	if (stat(path, &sb) != 0 || (fflag == 0 && cflag == 0 &&
	    lstat(path, &sb) != 0)) {
		/* lets try <path>.gz if we're decompressing */
		if (dflag && s == NULL && errno == ENOENT) {
			len = strlen(path);
			slen = suffixes[0].ziplen;
			s = malloc(len + slen + 1);
			if (s == NULL)
				maybe_err("malloc");
			memcpy(s, path, len);
			memcpy(s + len, suffixes[0].zipped, slen + 1);
			path = s;
			goto retry;
		}
		maybe_warn("can't stat: %s", opath);
		goto out;
	}

	if (S_ISDIR(sb.st_mode)) {
#ifndef SMALL
		if (rflag)
			handle_dir(path);
		else
#endif
			maybe_warnx("%s is a directory", path);
		goto out;
	}

	if (S_ISREG(sb.st_mode))
		handle_file(path, &sb);
	else
		maybe_warnx("%s is not a regular file", path);

out:
	if (s)
		free(s);
}