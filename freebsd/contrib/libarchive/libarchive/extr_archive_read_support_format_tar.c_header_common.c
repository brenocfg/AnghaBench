#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  s; } ;
struct tar {scalar_t__ entry_bytes_remaining; scalar_t__ realsize; int sparse_allowed; int /*<<< orphan*/  sconv; TYPE_1__ entry_linkpath; } ;
struct TYPE_6__ {int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_4__ archive; } ;
struct archive_entry_header_ustar {char* typeflag; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  mode; scalar_t__* linkname; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFBLK ; 
 int /*<<< orphan*/  AE_IFCHR ; 
 int /*<<< orphan*/  AE_IFDIR ; 
 int /*<<< orphan*/  AE_IFIFO ; 
 int /*<<< orphan*/  AE_IFLNK ; 
 int /*<<< orphan*/  AE_IFREG ; 
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_GNUTAR ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE ; 
 int ARCHIVE_OK ; 
 scalar_t__ INT64_MAX ; 
 int /*<<< orphan*/  archive_entry_copy_hardlink_l (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_copy_symlink_l (struct archive_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int archive_read_format_tar_bid (struct archive_read*,int) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_string_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_strlen (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_strncpy (TYPE_1__*,scalar_t__*,int) ; 
 int set_conversion_failed_error (struct archive_read*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tar_atol (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
header_common(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h)
{
	const struct archive_entry_header_ustar	*header;
	char	tartype;
	int     err = ARCHIVE_OK;

	header = (const struct archive_entry_header_ustar *)h;
	if (header->linkname[0])
		archive_strncpy(&(tar->entry_linkpath),
		    header->linkname, sizeof(header->linkname));
	else
		archive_string_empty(&(tar->entry_linkpath));

	/* Parse out the numeric fields (all are octal) */
	archive_entry_set_mode(entry,
		(mode_t)tar_atol(header->mode, sizeof(header->mode)));
	archive_entry_set_uid(entry, tar_atol(header->uid, sizeof(header->uid)));
	archive_entry_set_gid(entry, tar_atol(header->gid, sizeof(header->gid)));
	tar->entry_bytes_remaining = tar_atol(header->size, sizeof(header->size));
	if (tar->entry_bytes_remaining < 0) {
		tar->entry_bytes_remaining = 0;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Tar entry has negative size");
		return (ARCHIVE_FATAL);
	}
	if (tar->entry_bytes_remaining == INT64_MAX) {
		/* Note: tar_atol returns INT64_MAX on overflow */
		tar->entry_bytes_remaining = 0;
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Tar entry size overflow");
		return (ARCHIVE_FATAL);
	}
	tar->realsize = tar->entry_bytes_remaining;
	archive_entry_set_size(entry, tar->entry_bytes_remaining);
	archive_entry_set_mtime(entry, tar_atol(header->mtime, sizeof(header->mtime)), 0);

	/* Handle the tar type flag appropriately. */
	tartype = header->typeflag[0];

	switch (tartype) {
	case '1': /* Hard link */
		if (archive_entry_copy_hardlink_l(entry, tar->entry_linkpath.s,
		    archive_strlen(&(tar->entry_linkpath)), tar->sconv) != 0) {
			err = set_conversion_failed_error(a, tar->sconv,
			    "Linkname");
			if (err == ARCHIVE_FATAL)
				return (err);
		}
		/*
		 * The following may seem odd, but: Technically, tar
		 * does not store the file type for a "hard link"
		 * entry, only the fact that it is a hard link.  So, I
		 * leave the type zero normally.  But, pax interchange
		 * format allows hard links to have data, which
		 * implies that the underlying entry is a regular
		 * file.
		 */
		if (archive_entry_size(entry) > 0)
			archive_entry_set_filetype(entry, AE_IFREG);

		/*
		 * A tricky point: Traditionally, tar readers have
		 * ignored the size field when reading hardlink
		 * entries, and some writers put non-zero sizes even
		 * though the body is empty.  POSIX blessed this
		 * convention in the 1988 standard, but broke with
		 * this tradition in 2001 by permitting hardlink
		 * entries to store valid bodies in pax interchange
		 * format, but not in ustar format.  Since there is no
		 * hard and fast way to distinguish pax interchange
		 * from earlier archives (the 'x' and 'g' entries are
		 * optional, after all), we need a heuristic.
		 */
		if (archive_entry_size(entry) == 0) {
			/* If the size is already zero, we're done. */
		}  else if (a->archive.archive_format
		    == ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE) {
			/* Definitely pax extended; must obey hardlink size. */
		} else if (a->archive.archive_format == ARCHIVE_FORMAT_TAR
		    || a->archive.archive_format == ARCHIVE_FORMAT_TAR_GNUTAR)
		{
			/* Old-style or GNU tar: we must ignore the size. */
			archive_entry_set_size(entry, 0);
			tar->entry_bytes_remaining = 0;
		} else if (archive_read_format_tar_bid(a, 50) > 50) {
			/*
			 * We don't know if it's pax: If the bid
			 * function sees a valid ustar header
			 * immediately following, then let's ignore
			 * the hardlink size.
			 */
			archive_entry_set_size(entry, 0);
			tar->entry_bytes_remaining = 0;
		}
		/*
		 * TODO: There are still two cases I'd like to handle:
		 *   = a ustar non-pax archive with a hardlink entry at
		 *     end-of-archive.  (Look for block of nulls following?)
		 *   = a pax archive that has not seen any pax headers
		 *     and has an entry which is a hardlink entry storing
		 *     a body containing an uncompressed tar archive.
		 * The first is worth addressing; I don't see any reliable
		 * way to deal with the second possibility.
		 */
		break;
	case '2': /* Symlink */
		archive_entry_set_filetype(entry, AE_IFLNK);
		archive_entry_set_size(entry, 0);
		tar->entry_bytes_remaining = 0;
		if (archive_entry_copy_symlink_l(entry, tar->entry_linkpath.s,
		    archive_strlen(&(tar->entry_linkpath)), tar->sconv) != 0) {
			err = set_conversion_failed_error(a, tar->sconv,
			    "Linkname");
			if (err == ARCHIVE_FATAL)
				return (err);
		}
		break;
	case '3': /* Character device */
		archive_entry_set_filetype(entry, AE_IFCHR);
		archive_entry_set_size(entry, 0);
		tar->entry_bytes_remaining = 0;
		break;
	case '4': /* Block device */
		archive_entry_set_filetype(entry, AE_IFBLK);
		archive_entry_set_size(entry, 0);
		tar->entry_bytes_remaining = 0;
		break;
	case '5': /* Dir */
		archive_entry_set_filetype(entry, AE_IFDIR);
		archive_entry_set_size(entry, 0);
		tar->entry_bytes_remaining = 0;
		break;
	case '6': /* FIFO device */
		archive_entry_set_filetype(entry, AE_IFIFO);
		archive_entry_set_size(entry, 0);
		tar->entry_bytes_remaining = 0;
		break;
	case 'D': /* GNU incremental directory type */
		/*
		 * No special handling is actually required here.
		 * It might be nice someday to preprocess the file list and
		 * provide it to the client, though.
		 */
		archive_entry_set_filetype(entry, AE_IFDIR);
		break;
	case 'M': /* GNU "Multi-volume" (remainder of file from last archive)*/
		/*
		 * As far as I can tell, this is just like a regular file
		 * entry, except that the contents should be _appended_ to
		 * the indicated file at the indicated offset.  This may
		 * require some API work to fully support.
		 */
		break;
	case 'N': /* Old GNU "long filename" entry. */
		/* The body of this entry is a script for renaming
		 * previously-extracted entries.  Ugh.  It will never
		 * be supported by libarchive. */
		archive_entry_set_filetype(entry, AE_IFREG);
		break;
	case 'S': /* GNU sparse files */
		/*
		 * Sparse files are really just regular files with
		 * sparse information in the extended area.
		 */
		/* FALLTHROUGH */
	case '0':
		/*
		 * Enable sparse file "read" support only for regular
		 * files and explicit GNU sparse files.  However, we
		 * don't allow non-standard file types to be sparse.
		 */
		tar->sparse_allowed = 1;
		/* FALLTHROUGH */
	default: /* Regular file  and non-standard types */
		/*
		 * Per POSIX: non-recognized types should always be
		 * treated as regular files.
		 */
		archive_entry_set_filetype(entry, AE_IFREG);
		break;
	}
	return (err);
}