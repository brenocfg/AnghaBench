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
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive_string_conv {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
#define  AE_IFBLK 134 
#define  AE_IFCHR 133 
#define  AE_IFDIR 132 
#define  AE_IFIFO 131 
#define  AE_IFLNK 130 
#define  AE_IFREG 129 
#define  AE_IFSOCK 128 
 int /*<<< orphan*/  ARCHIVE_ERRNO_FILE_FORMAT ; 
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  ERANGE ; 
 int V7TAR_checksum_offset ; 
 int /*<<< orphan*/  V7TAR_gid_max_size ; 
 int V7TAR_gid_offset ; 
 int /*<<< orphan*/  V7TAR_gid_size ; 
 int V7TAR_linkname_offset ; 
 size_t V7TAR_linkname_size ; 
 int /*<<< orphan*/  V7TAR_mode_max_size ; 
 int V7TAR_mode_offset ; 
 int /*<<< orphan*/  V7TAR_mode_size ; 
 int /*<<< orphan*/  V7TAR_mtime_max_size ; 
 int V7TAR_mtime_offset ; 
 int /*<<< orphan*/  V7TAR_mtime_size ; 
 int V7TAR_name_offset ; 
 size_t V7TAR_name_size ; 
 int /*<<< orphan*/  V7TAR_size_max_size ; 
 int V7TAR_size_offset ; 
 int /*<<< orphan*/  V7TAR_size_size ; 
 size_t V7TAR_typeflag_offset ; 
 int /*<<< orphan*/  V7TAR_uid_max_size ; 
 int V7TAR_uid_offset ; 
 int /*<<< orphan*/  V7TAR_uid_size ; 
 int archive_entry_filetype (struct archive_entry*) ; 
 int archive_entry_gid (struct archive_entry*) ; 
 int archive_entry_hardlink_l (struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 int archive_entry_mtime (struct archive_entry*) ; 
 int archive_entry_pathname_l (struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int archive_entry_size (struct archive_entry*) ; 
 int archive_entry_symlink_l (struct archive_entry*,char const**,size_t*,struct archive_string_conv*) ; 
 int archive_entry_uid (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  archive_string_conversion_charset_name (struct archive_string_conv*) ; 
 scalar_t__ errno ; 
 scalar_t__ format_number (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  format_octal (unsigned int,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char const template_header ; 

__attribute__((used)) static int
format_header_v7tar(struct archive_write *a, char h[512],
    struct archive_entry *entry, int strict,
    struct archive_string_conv *sconv)
{
	unsigned int checksum;
	int i, r, ret;
	size_t copy_length;
	const char *p, *pp;
	int mytartype;

	ret = 0;
	mytartype = -1;
	/*
	 * The "template header" already includes the "v7tar"
	 * signature, various end-of-field markers and other required
	 * elements.
	 */
	memcpy(h, &template_header, 512);

	/*
	 * Because the block is already null-filled, and strings
	 * are allowed to exactly fill their destination (without null),
	 * I use memcpy(dest, src, strlen()) here a lot to copy strings.
	 */
	r = archive_entry_pathname_l(entry, &pp, &copy_length, sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Pathname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate pathname '%s' to %s",
		    pp, archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
	}
	if (strict && copy_length < V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else if (!strict && copy_length <= V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else {
		/* Prefix is too long. */
		archive_set_error(&a->archive, ENAMETOOLONG,
		    "Pathname too long");
		ret = ARCHIVE_FAILED;
	}

	r = archive_entry_hardlink_l(entry, &p, &copy_length, sconv);
	if (r != 0) {
		if (errno == ENOMEM) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory for Linkname");
			return (ARCHIVE_FATAL);
		}
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Can't translate linkname '%s' to %s",
		    p, archive_string_conversion_charset_name(sconv));
		ret = ARCHIVE_WARN;
	}
	if (copy_length > 0)
		mytartype = '1';
	else {
		r = archive_entry_symlink_l(entry, &p, &copy_length, sconv);
		if (r != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for Linkname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Can't translate linkname '%s' to %s",
			    p, archive_string_conversion_charset_name(sconv));
			ret = ARCHIVE_WARN;
		}
	}
	if (copy_length > 0) {
		if (copy_length >= V7TAR_linkname_size) {
			archive_set_error(&a->archive, ENAMETOOLONG,
			    "Link contents too long");
			ret = ARCHIVE_FAILED;
			copy_length = V7TAR_linkname_size;
		}
		memcpy(h + V7TAR_linkname_offset, p, copy_length);
	}

	if (format_number(archive_entry_mode(entry) & 07777,
	    h + V7TAR_mode_offset, V7TAR_mode_size,
	    V7TAR_mode_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric mode too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_uid(entry),
	    h + V7TAR_uid_offset, V7TAR_uid_size, V7TAR_uid_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_gid(entry),
	    h + V7TAR_gid_offset, V7TAR_gid_size, V7TAR_gid_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID too large");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_size(entry),
	    h + V7TAR_size_offset, V7TAR_size_size,
	    V7TAR_size_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "File size out of range");
		ret = ARCHIVE_FAILED;
	}

	if (format_number(archive_entry_mtime(entry),
	    h + V7TAR_mtime_offset, V7TAR_mtime_size,
	    V7TAR_mtime_max_size, strict)) {
		archive_set_error(&a->archive, ERANGE,
		    "File modification time too large");
		ret = ARCHIVE_FAILED;
	}

	if (mytartype >= 0) {
		h[V7TAR_typeflag_offset] = mytartype;
	} else {
		switch (archive_entry_filetype(entry)) {
		case AE_IFREG: case AE_IFDIR:
			break;
		case AE_IFLNK:
			h[V7TAR_typeflag_offset] = '2';
			break;
		case AE_IFCHR:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive character device");
			return (ARCHIVE_FAILED);
		case AE_IFBLK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive block device");
			return (ARCHIVE_FAILED);
		case AE_IFIFO:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive fifo");
			return (ARCHIVE_FAILED);
		case AE_IFSOCK:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive socket");
			return (ARCHIVE_FAILED);
		default:
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "tar format cannot archive this (mode=0%lo)",
			    (unsigned long)archive_entry_mode(entry));
			ret = ARCHIVE_FAILED;
		}
	}

	checksum = 0;
	for (i = 0; i < 512; i++)
		checksum += 255 & (unsigned int)h[i];
	format_octal(checksum, h + V7TAR_checksum_offset, 6);
	/* Can't be pre-set in the template. */
	h[V7TAR_checksum_offset + 6] = '\0';
	return (ret);
}