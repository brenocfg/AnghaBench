#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int state; } ;
struct TYPE_8__ {scalar_t__ st_size; } ;
struct archive_write_disk {int fd; scalar_t__ filesize; scalar_t__ fd_offset; int todo; int file_remaining_bytes; scalar_t__ user_uid; TYPE_2__ archive; int /*<<< orphan*/ * entry; int /*<<< orphan*/  mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  name; int /*<<< orphan*/ * pst; TYPE_1__ st; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  null_d ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_HEADER ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_DISK_MAGIC ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int TODO_ACLS ; 
 int TODO_APPLEDOUBLE ; 
 int TODO_FFLAGS ; 
 int TODO_HFS_COMPRESSION ; 
 int TODO_MAC_METADATA ; 
 int TODO_MODE ; 
 int TODO_OWNER ; 
 int TODO_SGID ; 
 int TODO_SUID ; 
 int TODO_TIMES ; 
 int TODO_XATTR ; 
 int /*<<< orphan*/  archive_check_magic (TYPE_2__*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_clear_error (TYPE_2__*) ; 
 int /*<<< orphan*/  archive_entry_acl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_gid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_gname (int /*<<< orphan*/ *) ; 
 void* archive_entry_mac_metadata (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  archive_entry_mode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_pathname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_uid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_entry_uname (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_disk_gid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int archive_write_disk_set_acls (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_write_disk_uid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int fixup_appledouble (struct archive_write_disk*,int /*<<< orphan*/ ) ; 
 int ftruncate (int,scalar_t__) ; 
 scalar_t__ hfs_write_data_block (struct archive_write_disk*,char*,int) ; 
 int lazy_stat (struct archive_write_disk*) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int set_fflags (struct archive_write_disk*) ; 
 int set_mac_metadata (struct archive_write_disk*,int /*<<< orphan*/ ,void const*,size_t) ; 
 int set_mode (struct archive_write_disk*,int /*<<< orphan*/ ) ; 
 int set_ownership (struct archive_write_disk*) ; 
 int set_times_from_entry (struct archive_write_disk*) ; 
 int set_xattrs (struct archive_write_disk*) ; 
 scalar_t__ write (int,char const*,int) ; 

__attribute__((used)) static int
_archive_write_disk_finish_entry(struct archive *_a)
{
	struct archive_write_disk *a = (struct archive_write_disk *)_a;
	int ret = ARCHIVE_OK;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_write_finish_entry");
	if (a->archive.state & ARCHIVE_STATE_HEADER)
		return (ARCHIVE_OK);
	archive_clear_error(&a->archive);

	/* Pad or truncate file to the right size. */
	if (a->fd < 0) {
		/* There's no file. */
	} else if (a->filesize < 0) {
		/* File size is unknown, so we can't set the size. */
	} else if (a->fd_offset == a->filesize) {
		/* Last write ended at exactly the filesize; we're done. */
		/* Hopefully, this is the common case. */
#if defined(__APPLE__) && defined(UF_COMPRESSED) && defined(HAVE_ZLIB_H)
	} else if (a->todo & TODO_HFS_COMPRESSION) {
		char null_d[1024];
		ssize_t r;

		if (a->file_remaining_bytes)
			memset(null_d, 0, sizeof(null_d));
		while (a->file_remaining_bytes) {
			if (a->file_remaining_bytes > sizeof(null_d))
				r = hfs_write_data_block(
				    a, null_d, sizeof(null_d));
			else
				r = hfs_write_data_block(
				    a, null_d, a->file_remaining_bytes);
			if (r < 0)
				return ((int)r);
		}
#endif
	} else {
#if HAVE_FTRUNCATE
		if (ftruncate(a->fd, a->filesize) == -1 &&
		    a->filesize == 0) {
			archive_set_error(&a->archive, errno,
			    "File size could not be restored");
			return (ARCHIVE_FAILED);
		}
#endif
		/*
		 * Not all platforms implement the XSI option to
		 * extend files via ftruncate.  Stat() the file again
		 * to see what happened.
		 */
		a->pst = NULL;
		if ((ret = lazy_stat(a)) != ARCHIVE_OK)
			return (ret);
		/* We can use lseek()/write() to extend the file if
		 * ftruncate didn't work or isn't available. */
		if (a->st.st_size < a->filesize) {
			const char nul = '\0';
			if (lseek(a->fd, a->filesize - 1, SEEK_SET) < 0) {
				archive_set_error(&a->archive, errno,
				    "Seek failed");
				return (ARCHIVE_FATAL);
			}
			if (write(a->fd, &nul, 1) < 0) {
				archive_set_error(&a->archive, errno,
				    "Write to restore size failed");
				return (ARCHIVE_FATAL);
			}
			a->pst = NULL;
		}
	}

	/* Restore metadata. */

	/*
	 * This is specific to Mac OS X.
	 * If the current file is an AppleDouble file, it should be
	 * linked with the data fork file and remove it.
	 */
	if (a->todo & TODO_APPLEDOUBLE) {
		int r2 = fixup_appledouble(a, a->name);
		if (r2 == ARCHIVE_EOF) {
			/* The current file has been successfully linked
			 * with the data fork file and removed. So there
			 * is nothing to do on the current file.  */
			goto finish_metadata;
		}
		if (r2 < ret) ret = r2;
	}

	/*
	 * Look up the "real" UID only if we're going to need it.
	 * TODO: the TODO_SGID condition can be dropped here, can't it?
	 */
	if (a->todo & (TODO_OWNER | TODO_SUID | TODO_SGID)) {
		a->uid = archive_write_disk_uid(&a->archive,
		    archive_entry_uname(a->entry),
		    archive_entry_uid(a->entry));
	}
	/* Look up the "real" GID only if we're going to need it. */
	/* TODO: the TODO_SUID condition can be dropped here, can't it? */
	if (a->todo & (TODO_OWNER | TODO_SGID | TODO_SUID)) {
		a->gid = archive_write_disk_gid(&a->archive,
		    archive_entry_gname(a->entry),
		    archive_entry_gid(a->entry));
	 }

	/*
	 * Restore ownership before set_mode tries to restore suid/sgid
	 * bits.  If we set the owner, we know what it is and can skip
	 * a stat() call to examine the ownership of the file on disk.
	 */
	if (a->todo & TODO_OWNER) {
		int r2 = set_ownership(a);
		if (r2 < ret) ret = r2;
	}

	/*
	 * HYPOTHESIS:
	 * If we're not root, we won't be setting any security
	 * attributes that may be wiped by the set_mode() routine
	 * below.  We also can't set xattr on non-owner-writable files,
	 * which may be the state after set_mode(). Perform
	 * set_xattrs() first based on these constraints.
	 */
	if (a->user_uid != 0 &&
	    (a->todo & TODO_XATTR)) {
		int r2 = set_xattrs(a);
		if (r2 < ret) ret = r2;
	}

	/*
	 * set_mode must precede ACLs on systems such as Solaris and
	 * FreeBSD where setting the mode implicitly clears extended ACLs
	 */
	if (a->todo & TODO_MODE) {
		int r2 = set_mode(a, a->mode);
		if (r2 < ret) ret = r2;
	}

	/*
	 * Security-related extended attributes (such as
	 * security.capability on Linux) have to be restored last,
	 * since they're implicitly removed by other file changes.
	 * We do this last only when root.
	 */
	if (a->user_uid == 0 &&
	    (a->todo & TODO_XATTR)) {
		int r2 = set_xattrs(a);
		if (r2 < ret) ret = r2;
	}

	/*
	 * Some flags prevent file modification; they must be restored after
	 * file contents are written.
	 */
	if (a->todo & TODO_FFLAGS) {
		int r2 = set_fflags(a);
		if (r2 < ret) ret = r2;
	}

	/*
	 * Time must follow most other metadata;
	 * otherwise atime will get changed.
	 */
	if (a->todo & TODO_TIMES) {
		int r2 = set_times_from_entry(a);
		if (r2 < ret) ret = r2;
	}

	/*
	 * Mac extended metadata includes ACLs.
	 */
	if (a->todo & TODO_MAC_METADATA) {
		const void *metadata;
		size_t metadata_size;
		metadata = archive_entry_mac_metadata(a->entry, &metadata_size);
		if (metadata != NULL && metadata_size > 0) {
			int r2 = set_mac_metadata(a, archive_entry_pathname(
			    a->entry), metadata, metadata_size);
			if (r2 < ret) ret = r2;
		}
	}

	/*
	 * ACLs must be restored after timestamps because there are
	 * ACLs that prevent attribute changes (including time).
	 */
	if (a->todo & TODO_ACLS) {
		int r2;
		r2 = archive_write_disk_set_acls(&a->archive, a->fd,
		    archive_entry_pathname(a->entry),
		    archive_entry_acl(a->entry),
		    archive_entry_mode(a->entry));
		if (r2 < ret) ret = r2;
	}

finish_metadata:
	/* If there's an fd, we can close it now. */
	if (a->fd >= 0) {
		close(a->fd);
		a->fd = -1;
	}
	/* If there's an entry, we can release it now. */
	archive_entry_free(a->entry);
	a->entry = NULL;
	a->archive.state = ARCHIVE_STATE_HEADER;
	return (ret);
}