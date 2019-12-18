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
struct stat {int st_mode; } ;
struct mlink {char* file; char* dsec; char* arch; char* fsec; char* name; int /*<<< orphan*/  dform; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  FORM_CAT ; 
 int /*<<< orphan*/  FORM_NONE ; 
 int /*<<< orphan*/  FORM_SRC ; 
 char* HOMEBREWDIR ; 
 scalar_t__ MANDOCLEVEL_BADARG ; 
 scalar_t__ OP_TEST ; 
 int PATH_MAX ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* basedir ; 
 int exitcode ; 
 int /*<<< orphan*/  free (struct mlink*) ; 
 int lstat (char const*,struct stat*) ; 
 struct mlink* mandoc_calloc (int,int) ; 
 int /*<<< orphan*/  mlink_add (struct mlink*,struct stat*) ; 
 scalar_t__ op ; 
 int /*<<< orphan*/ * realpath (char const*,char*) ; 
 int /*<<< orphan*/  say (char const*,char*,...) ; 
 int stat (char*,struct stat*) ; 
 char* strchr (char*,char) ; 
 int strlcpy (char*,char const*,int) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  use_all ; 

__attribute__((used)) static void
filescan(const char *file)
{
	char		 buf[PATH_MAX];
	struct stat	 st;
	struct mlink	*mlink;
	char		*p, *start;

	assert(use_all);

	if (0 == strncmp(file, "./", 2))
		file += 2;

	/*
	 * We have to do lstat(2) before realpath(3) loses
	 * the information whether this is a symbolic link.
	 * We need to know that because for symbolic links,
	 * we want to use the orginal file name, while for
	 * regular files, we want to use the real path.
	 */
	if (-1 == lstat(file, &st)) {
		exitcode = (int)MANDOCLEVEL_BADARG;
		say(file, "&lstat");
		return;
	} else if (0 == ((S_IFREG | S_IFLNK) & st.st_mode)) {
		exitcode = (int)MANDOCLEVEL_BADARG;
		say(file, "Not a regular file");
		return;
	}

	/*
	 * We have to resolve the file name to the real path
	 * in any case for the base directory check.
	 */
	if (NULL == realpath(file, buf)) {
		exitcode = (int)MANDOCLEVEL_BADARG;
		say(file, "&realpath");
		return;
	}

	if (OP_TEST == op)
		start = buf;
	else if (strstr(buf, basedir) == buf)
		start = buf + strlen(basedir);
#ifdef HOMEBREWDIR
	else if (strstr(buf, HOMEBREWDIR) == buf)
		start = buf;
#endif
	else {
		exitcode = (int)MANDOCLEVEL_BADARG;
		say("", "%s: outside base directory", buf);
		return;
	}

	/*
	 * Now we are sure the file is inside our tree.
	 * If it is a symbolic link, ignore the real path
	 * and use the original name.
	 * This implies passing stuff like "cat1/../man1/foo.1"
	 * on the command line won't work.  So don't do that.
	 * Note the stat(2) can still fail if the link target
	 * doesn't exist.
	 */
	if (S_IFLNK & st.st_mode) {
		if (-1 == stat(buf, &st)) {
			exitcode = (int)MANDOCLEVEL_BADARG;
			say(file, "&stat");
			return;
		}
		if (strlcpy(buf, file, sizeof(buf)) >= sizeof(buf)) {
			say(file, "Filename too long");
			return;
		}
		start = buf;
		if (OP_TEST != op && strstr(buf, basedir) == buf)
			start += strlen(basedir);
	}

	mlink = mandoc_calloc(1, sizeof(struct mlink));
	mlink->dform = FORM_NONE;
	if (strlcpy(mlink->file, start, sizeof(mlink->file)) >=
	    sizeof(mlink->file)) {
		say(start, "Filename too long");
		free(mlink);
		return;
	}

	/*
	 * In test mode or when the original name is absolute
	 * but outside our tree, guess the base directory.
	 */

	if (op == OP_TEST || (start == buf && *start == '/')) {
		if (strncmp(buf, "man/", 4) == 0)
			start = buf + 4;
		else if ((start = strstr(buf, "/man/")) != NULL)
			start += 5;
		else
			start = buf;
	}

	/*
	 * First try to guess our directory structure.
	 * If we find a separator, try to look for man* or cat*.
	 * If we find one of these and what's underneath is a directory,
	 * assume it's an architecture.
	 */
	if (NULL != (p = strchr(start, '/'))) {
		*p++ = '\0';
		if (0 == strncmp(start, "man", 3)) {
			mlink->dform = FORM_SRC;
			mlink->dsec = start + 3;
		} else if (0 == strncmp(start, "cat", 3)) {
			mlink->dform = FORM_CAT;
			mlink->dsec = start + 3;
		}

		start = p;
		if (NULL != mlink->dsec && NULL != (p = strchr(start, '/'))) {
			*p++ = '\0';
			mlink->arch = start;
			start = p;
		}
	}

	/*
	 * Now check the file suffix.
	 * Suffix of `.0' indicates a catpage, `.1-9' is a manpage.
	 */
	p = strrchr(start, '\0');
	while (p-- > start && '/' != *p && '.' != *p)
		/* Loop. */ ;

	if ('.' == *p) {
		*p++ = '\0';
		mlink->fsec = p;
	}

	/*
	 * Now try to parse the name.
	 * Use the filename portion of the path.
	 */
	mlink->name = start;
	if (NULL != (p = strrchr(start, '/'))) {
		mlink->name = p + 1;
		*p = '\0';
	}
	mlink_add(mlink, &st);
}