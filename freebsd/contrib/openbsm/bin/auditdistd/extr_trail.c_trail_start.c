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
struct trail {scalar_t__ tr_magic; char* tr_filename; int tr_filefd; int /*<<< orphan*/  tr_dirname; int /*<<< orphan*/  tr_dirfp; } ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRAIL_MAGIC ; 
 int /*<<< orphan*/  close (int) ; 
 int dirfd (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int fstat (int,struct stat*) ; 
 int lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int openat (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  pjdlog_warning (char*,int /*<<< orphan*/ ,char const*) ; 
 int strlcpy (char*,char const*,int) ; 
 scalar_t__ trail_find (struct trail*) ; 
 int /*<<< orphan*/  trail_is_crash_recovery (char const*) ; 
 scalar_t__ trail_is_not_terminated (char const*) ; 
 int /*<<< orphan*/  trail_next (struct trail*) ; 
 int unlinkat (int,char const*,int /*<<< orphan*/ ) ; 

void
trail_start(struct trail *trail, const char *filename, off_t offset)
{
	struct stat sb;
	int dfd, fd;

	PJDLOG_ASSERT(trail->tr_magic == TRAIL_MAGIC);

	PJDLOG_VERIFY(strlcpy(trail->tr_filename, filename,
	    sizeof(trail->tr_filename)) < sizeof(trail->tr_filename));
	trail->tr_filefd = -1;

	if (trail->tr_filename[0] == '\0') {
		PJDLOG_ASSERT(offset == 0);
		trail_next(trail);
		return;
	}

	dfd = dirfd(trail->tr_dirfp);
	PJDLOG_ASSERT(dfd >= 0);
again:
	fd = openat(dfd, trail->tr_filename, O_RDONLY);
	if (fd == -1) {
		if (errno == ENOENT &&
		    trail_is_not_terminated(trail->tr_filename) &&
		    trail_find(trail)) {
			/* File was renamed. Retry with new name. */
			pjdlog_debug(1,
			   "Trail file was renamed since last connection to \"%s/%s\".",
			   trail->tr_dirname, trail->tr_filename);
			goto again;
		} else if (errno == ENOENT) {
			/* File disappeared. */
			pjdlog_debug(1, "File \"%s/%s\" doesn't exist.",
			    trail->tr_dirname, trail->tr_filename);
		} else {
			pjdlog_errno(LOG_ERR,
			    "Unable to open file \"%s/%s\", skipping",
			    trail->tr_dirname, trail->tr_filename);
		}
		trail_next(trail);
		return;
	}
	if (fstat(fd, &sb) == -1) {
		pjdlog_errno(LOG_ERR,
		    "Unable to stat file \"%s/%s\", skipping",
		    trail->tr_dirname, trail->tr_filename);
		close(fd);
		trail_next(trail);
		return;
	}
	if (!S_ISREG(sb.st_mode)) {
		pjdlog_warning("File \"%s/%s\" is not a regular file, skipping.",
		    trail->tr_dirname, trail->tr_filename);
		close(fd);
		trail_next(trail);
		return;
	}
	/*
	 * We continue sending requested file if:
	 * 1. It is not fully sent yet, or
	 * 2. It is fully sent, but is not terminated, so new data can be
	 *    appended still, or
	 * 3. It is fully sent but file name has changed.
	 *    There are two cases here:
	 *    3a. Sender has crashed and the name has changed from
	 *        .not_terminated to .crash_recovery.
	 *    3b. Sender was disconnected, no new data was added to the file,
	 *        but its name has changed from .not_terminated to terminated
	 *        name.
	 *
	 * Note that we are fine if our .not_terminated or .crash_recovery file
	 * is smaller than the one on the receiver side, as it is possible that
	 * more data was send to the receiver than was safely stored on disk.
	 * We accept .not_terminated only because auditdistd can start before
	 * auditd manage to rename it to .crash_recovery.
	 */
	if (offset < sb.st_size ||
	    (offset >= sb.st_size &&
	     trail_is_not_terminated(trail->tr_filename)) ||
	    (offset >= sb.st_size && trail_is_not_terminated(filename) &&
	     !trail_is_not_terminated(trail->tr_filename))) {
		/* File was not fully send. Let's finish it. */
		if (lseek(fd, offset, SEEK_SET) == -1) {
			pjdlog_errno(LOG_ERR,
			    "Unable to move to offset %jd within file \"%s/%s\", skipping",
			    (intmax_t)offset, trail->tr_dirname,
			    trail->tr_filename);
			close(fd);
			trail_next(trail);
			return;
		}
		if (!trail_is_crash_recovery(trail->tr_filename)) {
			pjdlog_debug(1,
			    "Restarting file \"%s/%s\" at offset %jd.",
			    trail->tr_dirname, trail->tr_filename,
			    (intmax_t)offset);
		}
		trail->tr_filefd = fd;
		return;
	}
	close(fd);
	if (offset > sb.st_size) {
		pjdlog_warning("File \"%s/%s\" shrinked, removing it.",
		    trail->tr_dirname, trail->tr_filename);
	} else {
		pjdlog_debug(1, "File \"%s/%s\" is already sent, removing it.",
		    trail->tr_dirname, trail->tr_filename);
	}
	/* Entire file is already sent or it shirnked, we can remove it. */
	if (unlinkat(dfd, trail->tr_filename, 0) == -1) {
		pjdlog_errno(LOG_WARNING, "Unable to remove file \"%s/%s\"",
		    trail->tr_dirname, trail->tr_filename);
	}
	trail_next(trail);
}