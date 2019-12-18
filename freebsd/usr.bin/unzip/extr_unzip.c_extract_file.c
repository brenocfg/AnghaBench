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
struct timespec {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct TYPE_2__ {scalar_t__ tv_sec; scalar_t__ tv_nsec; } ;
struct stat {TYPE_1__ st_mtim; int /*<<< orphan*/  st_mode; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int O_TRUNC ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ UTIME_NOW ; 
 int archive_entry_mode (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime (struct archive_entry*) ; 
 scalar_t__ archive_entry_mtime_nsec (struct archive_entry*) ; 
 char* archive_entry_symlink (struct archive_entry*) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int extract2fd (struct archive*,char*,int) ; 
 scalar_t__ f_opt ; 
 scalar_t__ futimens (int,struct timespec*) ; 
 int handle_existing_file (char**) ; 
 int /*<<< orphan*/  info (char*,...) ; 
 scalar_t__ lchmod (char*,int) ; 
 scalar_t__ lstat (char*,struct stat*) ; 
 scalar_t__ n_opt ; 
 scalar_t__ o_opt ; 
 int open (char*,int,int) ; 
 scalar_t__ symlink (char const*,char*) ; 
 scalar_t__ tty ; 
 scalar_t__ u_opt ; 
 int /*<<< orphan*/  unlink (char*) ; 
 scalar_t__ utimensat (int /*<<< orphan*/ ,char*,struct timespec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (char*,char*) ; 

__attribute__((used)) static void
extract_file(struct archive *a, struct archive_entry *e, char **path)
{
	int mode;
	struct timespec mtime;
	struct stat sb;
	struct timespec ts[2];
	int fd, check, text;
	const char *linkname;

	mode = archive_entry_mode(e) & 0777;
	if (mode == 0)
		mode = 0644;
	mtime.tv_sec = archive_entry_mtime(e);
	mtime.tv_nsec = archive_entry_mtime_nsec(e);

	/* look for existing file of same name */
recheck:
	if (lstat(*path, &sb) == 0) {
		if (u_opt || f_opt) {
			/* check if up-to-date */
			if ((S_ISREG(sb.st_mode) || S_ISLNK(sb.st_mode)) &&
			    (sb.st_mtim.tv_sec > mtime.tv_sec ||
			    (sb.st_mtim.tv_sec == mtime.tv_sec &&
			    sb.st_mtim.tv_nsec >= mtime.tv_nsec)))
				return;
			(void)unlink(*path);
		} else if (o_opt) {
			/* overwrite */
			(void)unlink(*path);
		} else if (n_opt) {
			/* do not overwrite */
			return;
		} else {
			check = handle_existing_file(path);
			if (check == 0)
				goto recheck;
			if (check == -1)
				return; /* do not overwrite */
		}
	} else {
		if (f_opt)
			return;
	}

	ts[0].tv_sec = 0;
	ts[0].tv_nsec = UTIME_NOW;
	ts[1] = mtime;

	/* process symlinks */
	linkname = archive_entry_symlink(e);
	if (linkname != NULL) {
		if (symlink(linkname, *path) != 0)
			error("symlink('%s')", *path);
		info(" extracting: %s -> %s\n", *path, linkname);
		if (lchmod(*path, mode) != 0)
			warning("Cannot set mode for '%s'", *path);
		/* set access and modification time */
		if (utimensat(AT_FDCWD, *path, ts, AT_SYMLINK_NOFOLLOW) != 0)
			warning("utimensat('%s')", *path);
		return;
	}

	if ((fd = open(*path, O_RDWR|O_CREAT|O_TRUNC, mode)) < 0)
		error("open('%s')", *path);

	info(" extracting: %s", *path);

	text = extract2fd(a, *path, fd);

	if (tty)
		info("  \b\b");
	if (text)
		info(" (text)");
	info("\n");

	/* set access and modification time */
	if (futimens(fd, ts) != 0)
		error("futimens('%s')", *path);
	if (close(fd) != 0)
		error("close('%s')", *path);
}