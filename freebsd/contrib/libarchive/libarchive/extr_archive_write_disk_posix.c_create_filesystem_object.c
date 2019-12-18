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
struct archive_write_disk {int flags; scalar_t__ filesize; int todo; int deferred; scalar_t__ fd; int mode; int user_umask; scalar_t__ user_uid; int /*<<< orphan*/  name; int /*<<< orphan*/  entry; int /*<<< orphan*/  archive; } ;
struct archive_string {int /*<<< orphan*/  s; } ;
typedef  int mode_t ;

/* Variables and functions */
#define  AE_IFBLK 132 
#define  AE_IFCHR 131 
#define  AE_IFDIR 130 
#define  AE_IFIFO 129 
 int AE_IFMT ; 
#define  AE_IFREG 128 
 int ARCHIVE_EXTRACT_PERM ; 
 int ARCHIVE_OK ; 
 int EINVAL ; 
 int EPERM ; 
 int MAXIMUM_DIR_MODE ; 
 int MINIMUM_DIR_MODE ; 
 int O_BINARY ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_NOFOLLOW ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int S_IFBLK ; 
 int S_IFCHR ; 
 int TODO_HFS_COMPRESSION ; 
 int TODO_MODE ; 
 int TODO_TIMES ; 
 int TODO_XATTR ; 
 int /*<<< orphan*/  __archive_ensure_cloexec_flag (scalar_t__) ; 
 char* archive_entry_hardlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_rdev (int /*<<< orphan*/ ) ; 
 char* archive_entry_symlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (struct archive_string*) ; 
 int /*<<< orphan*/  archive_string_init (struct archive_string*) ; 
 int check_symlinks_fsobj (char*,int*,struct archive_string*,int) ; 
 int cleanup_pathname_fsobj (char*,int*,struct archive_string*,int) ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int la_stat (int /*<<< orphan*/ ,struct stat*) ; 
 scalar_t__ link (char const*,int /*<<< orphan*/ ) ; 
 int lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int mkdir (int /*<<< orphan*/ ,int) ; 
 int mkfifo (int /*<<< orphan*/ ,int) ; 
 int mknod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* open (int /*<<< orphan*/ ,int,...) ; 
 char* strdup (char const*) ; 
 scalar_t__ symlink (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
create_filesystem_object(struct archive_write_disk *a)
{
	/* Create the entry. */
	const char *linkname;
	mode_t final_mode, mode;
	int r;
	/* these for check_symlinks_fsobj */
	char *linkname_copy;	/* non-const copy of linkname */
	struct stat st;
	struct archive_string error_string;
	int error_number;

	/* We identify hard/symlinks according to the link names. */
	/* Since link(2) and symlink(2) don't handle modes, we're done here. */
	linkname = archive_entry_hardlink(a->entry);
	if (linkname != NULL) {
#if !HAVE_LINK
		return (EPERM);
#else
		archive_string_init(&error_string);
		linkname_copy = strdup(linkname);
		if (linkname_copy == NULL) {
		    return (EPERM);
		}
		/*
		 * TODO: consider using the cleaned-up path as the link
		 * target?
		 */
		r = cleanup_pathname_fsobj(linkname_copy, &error_number,
		    &error_string, a->flags);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, error_number, "%s",
			    error_string.s);
			free(linkname_copy);
			archive_string_free(&error_string);
			/*
			 * EPERM is more appropriate than error_number for our
			 * callers
			 */
			return (EPERM);
		}
		r = check_symlinks_fsobj(linkname_copy, &error_number,
		    &error_string, a->flags);
		if (r != ARCHIVE_OK) {
			archive_set_error(&a->archive, error_number, "%s",
			    error_string.s);
			free(linkname_copy);
			archive_string_free(&error_string);
			/*
			 * EPERM is more appropriate than error_number for our
			 * callers
			 */
			return (EPERM);
		}
		free(linkname_copy);
		archive_string_free(&error_string);
		r = link(linkname, a->name) ? errno : 0;
		/*
		 * New cpio and pax formats allow hardlink entries
		 * to carry data, so we may have to open the file
		 * for hardlink entries.
		 *
		 * If the hardlink was successfully created and
		 * the archive doesn't have carry data for it,
		 * consider it to be non-authoritative for meta data.
		 * This is consistent with GNU tar and BSD pax.
		 * If the hardlink does carry data, let the last
		 * archive entry decide ownership.
		 */
		if (r == 0 && a->filesize <= 0) {
			a->todo = 0;
			a->deferred = 0;
		} else if (r == 0 && a->filesize > 0) {
#ifdef HAVE_LSTAT
			r = lstat(a->name, &st);
#else
			r = la_stat(a->name, &st);
#endif
			if (r != 0)
				r = errno;
			else if ((st.st_mode & AE_IFMT) == AE_IFREG) {
				a->fd = open(a->name, O_WRONLY | O_TRUNC |
				    O_BINARY | O_CLOEXEC | O_NOFOLLOW);
				__archive_ensure_cloexec_flag(a->fd);
				if (a->fd < 0)
					r = errno;
			}
		}
		return (r);
#endif
	}
	linkname = archive_entry_symlink(a->entry);
	if (linkname != NULL) {
#if HAVE_SYMLINK
		return symlink(linkname, a->name) ? errno : 0;
#else
		return (EPERM);
#endif
	}

	/*
	 * The remaining system calls all set permissions, so let's
	 * try to take advantage of that to avoid an extra chmod()
	 * call.  (Recall that umask is set to zero right now!)
	 */

	/* Mode we want for the final restored object (w/o file type bits). */
	final_mode = a->mode & 07777;
	/*
	 * The mode that will actually be restored in this step.  Note
	 * that SUID, SGID, etc, require additional work to ensure
	 * security, so we never restore them at this point.
	 */
	mode = final_mode & 0777 & ~a->user_umask;

	/* 
	 * Always create writable such that [f]setxattr() works if we're not
	 * root.
	 */
	if (a->user_uid != 0 &&
	    a->todo & (TODO_HFS_COMPRESSION | TODO_XATTR)) {
		mode |= 0200;
	}

	switch (a->mode & AE_IFMT) {
	default:
		/* POSIX requires that we fall through here. */
		/* FALLTHROUGH */
	case AE_IFREG:
		a->fd = open(a->name,
		    O_WRONLY | O_CREAT | O_EXCL | O_BINARY | O_CLOEXEC, mode);
		__archive_ensure_cloexec_flag(a->fd);
		r = (a->fd < 0);
		break;
	case AE_IFCHR:
#ifdef HAVE_MKNOD
		/* Note: we use AE_IFCHR for the case label, and
		 * S_IFCHR for the mknod() call.  This is correct.  */
		r = mknod(a->name, mode | S_IFCHR,
		    archive_entry_rdev(a->entry));
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a char device node. */
		return (EINVAL);
#endif /* HAVE_MKNOD */
	case AE_IFBLK:
#ifdef HAVE_MKNOD
		r = mknod(a->name, mode | S_IFBLK,
		    archive_entry_rdev(a->entry));
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a block device node. */
		return (EINVAL);
#endif /* HAVE_MKNOD */
	case AE_IFDIR:
		mode = (mode | MINIMUM_DIR_MODE) & MAXIMUM_DIR_MODE;
		r = mkdir(a->name, mode);
		if (r == 0) {
			/* Defer setting dir times. */
			a->deferred |= (a->todo & TODO_TIMES);
			a->todo &= ~TODO_TIMES;
			/* Never use an immediate chmod(). */
			/* We can't avoid the chmod() entirely if EXTRACT_PERM
			 * because of SysV SGID inheritance. */
			if ((mode != final_mode)
			    || (a->flags & ARCHIVE_EXTRACT_PERM))
				a->deferred |= (a->todo & TODO_MODE);
			a->todo &= ~TODO_MODE;
		}
		break;
	case AE_IFIFO:
#ifdef HAVE_MKFIFO
		r = mkfifo(a->name, mode);
		break;
#else
		/* TODO: Find a better way to warn about our inability
		 * to restore a fifo. */
		return (EINVAL);
#endif /* HAVE_MKFIFO */
	}

	/* All the system calls above set errno on failure. */
	if (r)
		return (errno);

	/* If we managed to set the final mode, we've avoided a chmod(). */
	if (mode == final_mode)
		a->todo &= ~TODO_MODE;
	return (0);
}