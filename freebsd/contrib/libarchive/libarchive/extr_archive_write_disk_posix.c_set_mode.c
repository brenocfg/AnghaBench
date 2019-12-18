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
struct archive_write_disk {int todo; scalar_t__ gid; int flags; scalar_t__ uid; scalar_t__ user_uid; scalar_t__ fd; int /*<<< orphan*/  archive; int /*<<< orphan*/  name; int /*<<< orphan*/  mode; TYPE_1__* pst; } ;
struct TYPE_2__ {scalar_t__ st_gid; scalar_t__ st_uid; } ;

/* Variables and functions */
 int ARCHIVE_EXTRACT_OWNER ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
#define  ENOSYS 130 
#define  ENOTSUP 129 
#define  EOPNOTSUPP 128 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_ISGID ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int S_ISUID ; 
 int TODO_SGID_CHECK ; 
 int TODO_SUID ; 
 int TODO_SUID_CHECK ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*,...) ; 
 int chmod (int /*<<< orphan*/ ,int) ; 
 int errno ; 
 int fchmod (scalar_t__,int) ; 
 int lazy_stat (struct archive_write_disk*) ; 
 scalar_t__ lchmod (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
set_mode(struct archive_write_disk *a, int mode)
{
	int r = ARCHIVE_OK;
	int r2;
	mode &= 07777; /* Strip off file type bits. */

	if (a->todo & TODO_SGID_CHECK) {
		/*
		 * If we don't know the GID is right, we must stat()
		 * to verify it.  We can't just check the GID of this
		 * process, since systems sometimes set GID from
		 * the enclosing dir or based on ACLs.
		 */
		if ((r = lazy_stat(a)) != ARCHIVE_OK)
			return (r);
		if (a->pst->st_gid != a->gid) {
			mode &= ~ S_ISGID;
			if (a->flags & ARCHIVE_EXTRACT_OWNER) {
				/*
				 * This is only an error if you
				 * requested owner restore.  If you
				 * didn't, we'll try to restore
				 * sgid/suid, but won't consider it a
				 * problem if we can't.
				 */
				archive_set_error(&a->archive, -1,
				    "Can't restore SGID bit");
				r = ARCHIVE_WARN;
			}
		}
		/* While we're here, double-check the UID. */
		if (a->pst->st_uid != a->uid
		    && (a->todo & TODO_SUID)) {
			mode &= ~ S_ISUID;
			if (a->flags & ARCHIVE_EXTRACT_OWNER) {
				archive_set_error(&a->archive, -1,
				    "Can't restore SUID bit");
				r = ARCHIVE_WARN;
			}
		}
		a->todo &= ~TODO_SGID_CHECK;
		a->todo &= ~TODO_SUID_CHECK;
	} else if (a->todo & TODO_SUID_CHECK) {
		/*
		 * If we don't know the UID is right, we can just check
		 * the user, since all systems set the file UID from
		 * the process UID.
		 */
		if (a->user_uid != a->uid) {
			mode &= ~ S_ISUID;
			if (a->flags & ARCHIVE_EXTRACT_OWNER) {
				archive_set_error(&a->archive, -1,
				    "Can't make file SUID");
				r = ARCHIVE_WARN;
			}
		}
		a->todo &= ~TODO_SUID_CHECK;
	}

	if (S_ISLNK(a->mode)) {
#ifdef HAVE_LCHMOD
		/*
		 * If this is a symlink, use lchmod().  If the
		 * platform doesn't support lchmod(), just skip it.  A
		 * platform that doesn't provide a way to set
		 * permissions on symlinks probably ignores
		 * permissions on symlinks, so a failure here has no
		 * impact.
		 */
		if (lchmod(a->name, mode) != 0) {
			switch (errno) {
			case ENOTSUP:
			case ENOSYS:
#if ENOTSUP != EOPNOTSUPP
			case EOPNOTSUPP:
#endif
				/*
				 * if lchmod is defined but the platform
				 * doesn't support it, silently ignore
				 * error
				 */
				break;
			default:
				archive_set_error(&a->archive, errno,
				    "Can't set permissions to 0%o", (int)mode);
				r = ARCHIVE_WARN;
			}
		}
#endif
	} else if (!S_ISDIR(a->mode)) {
		/*
		 * If it's not a symlink and not a dir, then use
		 * fchmod() or chmod(), depending on whether we have
		 * an fd.  Dirs get their perms set during the
		 * post-extract fixup, which is handled elsewhere.
		 */
#ifdef HAVE_FCHMOD
		if (a->fd >= 0)
			r2 = fchmod(a->fd, mode);
		else
#endif
		/* If this platform lacks fchmod(), then
		 * we'll just use chmod(). */
		r2 = chmod(a->name, mode);

		if (r2 != 0) {
			archive_set_error(&a->archive, errno,
			    "Can't set permissions to 0%o", (int)mode);
			r = ARCHIVE_WARN;
		}
	}
	return (r);
}