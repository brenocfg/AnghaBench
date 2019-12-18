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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_EXTRACT_SECURE_SYMLINKS ; 
 int ARCHIVE_EXTRACT_UNLINK ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int AT_FDCWD ; 
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 scalar_t__ ENOENT ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (int) ; 
 int chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error_number ; 
 int /*<<< orphan*/  error_string ; 
 int fchdir (int) ; 
 int /*<<< orphan*/  fsobj_error (int*,struct archive_string*,scalar_t__,char*,char*) ; 
 int fstatat (int,char*,struct stat*,int /*<<< orphan*/ ) ; 
 int la_opendirat (int,char*) ; 
 int la_stat (char*,struct stat*) ; 
 int lstat (char*,struct stat*) ; 
 int unlink (char*) ; 
 int unlinkat (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,
    int flags)
{
#if !defined(HAVE_LSTAT) && \
    !(defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT))
	/* Platform doesn't have lstat, so we can't look for symlinks. */
	(void)path; /* UNUSED */
	(void)error_number; /* UNUSED */
	(void)error_string; /* UNUSED */
	(void)flags; /* UNUSED */
	return (ARCHIVE_OK);
#else
	int res = ARCHIVE_OK;
	char *tail;
	char *head;
	int last;
	char c;
	int r;
	struct stat st;
	int chdir_fd;
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
	int fd;
#endif

	/* Nothing to do here if name is empty */
	if(path[0] == '\0')
	    return (ARCHIVE_OK);

	/*
	 * Guard against symlink tricks.  Reject any archive entry whose
	 * destination would be altered by a symlink.
	 *
	 * Walk the filename in chunks separated by '/'.  For each segment:
	 *  - if it doesn't exist, continue
	 *  - if it's symlink, abort or remove it
	 *  - if it's a directory and it's not the last chunk, cd into it
	 * As we go:
	 *  head points to the current (relative) path
	 *  tail points to the temporary \0 terminating the segment we're
	 *      currently examining
	 *  c holds what used to be in *tail
	 *  last is 1 if this is the last tail
	 */
	chdir_fd = la_opendirat(AT_FDCWD, ".");
	__archive_ensure_cloexec_flag(chdir_fd);
	if (chdir_fd < 0) {
		fsobj_error(a_eno, a_estr, errno,
		    "Could not open ", path);
		return (ARCHIVE_FATAL);
	}
	head = path;
	tail = path;
	last = 0;
	/* TODO: reintroduce a safe cache here? */
	/* Skip the root directory if the path is absolute. */
	if(tail == path && tail[0] == '/')
		++tail;
	/* Keep going until we've checked the entire name.
	 * head, tail, path all alias the same string, which is
	 * temporarily zeroed at tail, so be careful restoring the
	 * stashed (c=tail[0]) for error messages.
	 * Exiting the loop with break is okay; continue is not.
	 */
	while (!last) {
		/*
		 * Skip the separator we just consumed, plus any adjacent ones
		 */
		while (*tail == '/')
		    ++tail;
		/* Skip the next path element. */
		while (*tail != '\0' && *tail != '/')
			++tail;
		/* is this the last path component? */
		last = (tail[0] == '\0') || (tail[0] == '/' && tail[1] == '\0');
		/* temporarily truncate the string here */
		c = tail[0];
		tail[0] = '\0';
		/* Check that we haven't hit a symlink. */
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
		r = fstatat(chdir_fd, head, &st, AT_SYMLINK_NOFOLLOW);
#else
		r = lstat(head, &st);
#endif
		if (r != 0) {
			tail[0] = c;
			/* We've hit a dir that doesn't exist; stop now. */
			if (errno == ENOENT) {
				break;
			} else {
				/*
				 * Treat any other error as fatal - best to be
				 * paranoid here.
				 * Note: This effectively disables deep
				 * directory support when security checks are
				 * enabled. Otherwise, very long pathnames that
				 * trigger an error here could evade the
				 * sandbox.
				 * TODO: We could do better, but it would
				 * probably require merging the symlink checks
				 * with the deep-directory editing.
				 */
				fsobj_error(a_eno, a_estr, errno,
				    "Could not stat ", path);
				res = ARCHIVE_FAILED;
				break;
			}
		} else if (S_ISDIR(st.st_mode)) {
			if (!last) {
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				fd = la_opendirat(chdir_fd, head);
				if (fd < 0)
					r = -1;
				else {
					r = 0;
					close(chdir_fd);
					chdir_fd = fd;
				}
#else
				r = chdir(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not chdir ", path);
					res = (ARCHIVE_FATAL);
					break;
				}
				/* Our view is now from inside this dir: */
				head = tail + 1;
			}
		} else if (S_ISLNK(st.st_mode)) {
			if (last) {
				/*
				 * Last element is symlink; remove it
				 * so we can overwrite it with the
				 * item being extracted.
				 */
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = unlinkat(chdir_fd, head, 0);
#else
				r = unlink(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, errno,
					    "Could not remove symlink ",
					    path);
					res = ARCHIVE_FAILED;
					break;
				}
				/*
				 * Even if we did remove it, a warning
				 * is in order.  The warning is silly,
				 * though, if we're just replacing one
				 * symlink with another symlink.
				 */
				tail[0] = c;
				/*
				 * FIXME:  not sure how important this is to
				 * restore
				 */
				/*
				if (!S_ISLNK(path)) {
					fsobj_error(a_eno, a_estr, 0,
					    "Removing symlink ", path);
				}
				*/
				/* Symlink gone.  No more problem! */
				res = ARCHIVE_OK;
				break;
			} else if (flags & ARCHIVE_EXTRACT_UNLINK) {
				/* User asked us to remove problems. */
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = unlinkat(chdir_fd, head, 0);
#else
				r = unlink(head);
#endif
				if (r != 0) {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot remove intervening "
					    "symlink ", path);
					res = ARCHIVE_FAILED;
					break;
				}
				tail[0] = c;
			} else if ((flags &
			    ARCHIVE_EXTRACT_SECURE_SYMLINKS) == 0) {
				/*
				 * We are not the last element and we want to
				 * follow symlinks if they are a directory.
				 * 
				 * This is needed to extract hardlinks over
				 * symlinks.
				 */
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
				r = fstatat(chdir_fd, head, &st, 0);
#else
				r = la_stat(head, &st);
#endif
				if (r != 0) {
					tail[0] = c;
					if (errno == ENOENT) {
						break;
					} else {
						fsobj_error(a_eno, a_estr,
						    errno,
						    "Could not stat ", path);
						res = (ARCHIVE_FAILED);
						break;
					}
				} else if (S_ISDIR(st.st_mode)) {
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
					fd = la_opendirat(chdir_fd, head);
					if (fd < 0)
						r = -1;
					else {
						r = 0;
						close(chdir_fd);
						chdir_fd = fd;
					}
#else
					r = chdir(head);
#endif
					if (r != 0) {
						tail[0] = c;
						fsobj_error(a_eno, a_estr,
						    errno,
						    "Could not chdir ", path);
						res = (ARCHIVE_FATAL);
						break;
					}
					/*
					 * Our view is now from inside
					 * this dir:
					 */
					head = tail + 1;
				} else {
					tail[0] = c;
					fsobj_error(a_eno, a_estr, 0,
					    "Cannot extract through "
					    "symlink ", path);
					res = ARCHIVE_FAILED;
					break;
				}
			} else {
				tail[0] = c;
				fsobj_error(a_eno, a_estr, 0,
				    "Cannot extract through symlink ", path);
				res = ARCHIVE_FAILED;
				break;
			}
		}
		/* be sure to always maintain this */
		tail[0] = c;
		if (tail[0] != '\0')
			tail++; /* Advance to the next segment. */
	}
	/* Catches loop exits via break */
	tail[0] = c;
#if defined(HAVE_OPENAT) && defined(HAVE_FSTATAT) && defined(HAVE_UNLINKAT)
	/* If we operate with openat(), fstatat() and unlinkat() there was
	 * no chdir(), so just close the fd */
	if (chdir_fd >= 0)
		close(chdir_fd);
#elif HAVE_FCHDIR
	/* If we changed directory above, restore it here. */
	if (chdir_fd >= 0) {
		r = fchdir(chdir_fd);
		if (r != 0) {
			fsobj_error(a_eno, a_estr, errno,
			    "chdir() failure", "");
		}
		close(chdir_fd);
		chdir_fd = -1;
		if (r != 0) {
			res = (ARCHIVE_FATAL);
		}
	}
#endif
	/* TODO: reintroduce a safe cache here? */
	return res;
#endif
}