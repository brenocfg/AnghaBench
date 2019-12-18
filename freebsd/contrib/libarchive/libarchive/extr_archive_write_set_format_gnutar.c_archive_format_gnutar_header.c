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
struct gnutar {char* pathname; size_t pathname_length; size_t linkname_length; char const* linkname; char* uname; size_t uname_length; char* gname; size_t gname_length; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ AE_IFBLK ; 
 scalar_t__ AE_IFCHR ; 
 int ARCHIVE_FAILED ; 
 int /*<<< orphan*/  ERANGE ; 
 int GNUTAR_checksum_offset ; 
 int /*<<< orphan*/  GNUTAR_gid_max_size ; 
 int GNUTAR_gid_offset ; 
 int /*<<< orphan*/  GNUTAR_gid_size ; 
 int GNUTAR_gname_offset ; 
 size_t GNUTAR_gname_size ; 
 int GNUTAR_linkname_offset ; 
 size_t GNUTAR_linkname_size ; 
 int GNUTAR_mode_offset ; 
 int GNUTAR_mode_size ; 
 int GNUTAR_mtime_offset ; 
 int GNUTAR_mtime_size ; 
 int GNUTAR_name_offset ; 
 size_t GNUTAR_name_size ; 
 int GNUTAR_rdevmajor_offset ; 
 int GNUTAR_rdevmajor_size ; 
 int GNUTAR_rdevminor_offset ; 
 int GNUTAR_rdevminor_size ; 
 int /*<<< orphan*/  GNUTAR_size_max_size ; 
 int GNUTAR_size_offset ; 
 int /*<<< orphan*/  GNUTAR_size_size ; 
 size_t GNUTAR_typeflag_offset ; 
 int /*<<< orphan*/  GNUTAR_uid_max_size ; 
 int GNUTAR_uid_offset ; 
 int /*<<< orphan*/  GNUTAR_uid_size ; 
 int GNUTAR_uname_offset ; 
 size_t GNUTAR_uname_size ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 scalar_t__ archive_entry_gid (struct archive_entry*) ; 
 char* archive_entry_gname (struct archive_entry*) ; 
 int archive_entry_mode (struct archive_entry*) ; 
 unsigned int archive_entry_mtime (struct archive_entry*) ; 
 char* archive_entry_pathname (struct archive_entry*) ; 
 unsigned int archive_entry_rdevmajor (struct archive_entry*) ; 
 unsigned int archive_entry_rdevminor (struct archive_entry*) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 scalar_t__ archive_entry_uid (struct archive_entry*) ; 
 char* archive_entry_uname (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ format_number (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ format_octal (unsigned int,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 char const template_header ; 

__attribute__((used)) static int
archive_format_gnutar_header(struct archive_write *a, char h[512],
    struct archive_entry *entry, int tartype)
{
	unsigned int checksum;
	int i, ret;
	size_t copy_length;
	const char *p;
	struct gnutar *gnutar;

	gnutar = (struct gnutar *)a->format_data;

	ret = 0;

	/*
	 * The "template header" already includes the signature,
	 * various end-of-field markers, and other required elements.
	 */
	memcpy(h, &template_header, 512);

	/*
	 * Because the block is already null-filled, and strings
	 * are allowed to exactly fill their destination (without null),
	 * I use memcpy(dest, src, strlen()) here a lot to copy strings.
	 */

	if (tartype == 'K' || tartype == 'L') {
		p = archive_entry_pathname(entry);
		copy_length = strlen(p);
	} else {
		p = gnutar->pathname;
		copy_length = gnutar->pathname_length;
	}
	if (copy_length > GNUTAR_name_size)
		copy_length = GNUTAR_name_size;
	memcpy(h + GNUTAR_name_offset, p, copy_length);

	if ((copy_length = gnutar->linkname_length) > 0) {
		if (copy_length > GNUTAR_linkname_size)
			copy_length = GNUTAR_linkname_size;
		memcpy(h + GNUTAR_linkname_offset, gnutar->linkname,
		    copy_length);
	}

	/* TODO: How does GNU tar handle unames longer than GNUTAR_uname_size? */
	if (tartype == 'K' || tartype == 'L') {
		p = archive_entry_uname(entry);
		copy_length = strlen(p);
	} else {
		p = gnutar->uname;
		copy_length = gnutar->uname_length;
	}
	if (copy_length > 0) {
		if (copy_length > GNUTAR_uname_size)
			copy_length = GNUTAR_uname_size;
		memcpy(h + GNUTAR_uname_offset, p, copy_length);
	}

	/* TODO: How does GNU tar handle gnames longer than GNUTAR_gname_size? */
	if (tartype == 'K' || tartype == 'L') {
		p = archive_entry_gname(entry);
		copy_length = strlen(p);
	} else {
		p = gnutar->gname;
		copy_length = gnutar->gname_length;
	}
	if (copy_length > 0) {
		if (strlen(p) > GNUTAR_gname_size)
			copy_length = GNUTAR_gname_size;
		memcpy(h + GNUTAR_gname_offset, p, copy_length);
	}

	/* By truncating the mode here, we ensure it always fits. */
	format_octal(archive_entry_mode(entry) & 07777,
	    h + GNUTAR_mode_offset, GNUTAR_mode_size);

	/* GNU tar supports base-256 here, so should never overflow. */
	if (format_number(archive_entry_uid(entry), h + GNUTAR_uid_offset,
		GNUTAR_uid_size, GNUTAR_uid_max_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric user ID %jd too large",
		    (intmax_t)archive_entry_uid(entry));
		ret = ARCHIVE_FAILED;
	}

	/* GNU tar supports base-256 here, so should never overflow. */
	if (format_number(archive_entry_gid(entry), h + GNUTAR_gid_offset,
		GNUTAR_gid_size, GNUTAR_gid_max_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "Numeric group ID %jd too large",
		    (intmax_t)archive_entry_gid(entry));
		ret = ARCHIVE_FAILED;
	}

	/* GNU tar supports base-256 here, so should never overflow. */
	if (format_number(archive_entry_size(entry), h + GNUTAR_size_offset,
		GNUTAR_size_size, GNUTAR_size_max_size)) {
		archive_set_error(&a->archive, ERANGE,
		    "File size out of range");
		ret = ARCHIVE_FAILED;
	}

	/* Shouldn't overflow before 2106, since mtime field is 33 bits. */
	format_octal(archive_entry_mtime(entry),
	    h + GNUTAR_mtime_offset, GNUTAR_mtime_size);

	if (archive_entry_filetype(entry) == AE_IFBLK
	    || archive_entry_filetype(entry) == AE_IFCHR) {
		if (format_octal(archive_entry_rdevmajor(entry),
		    h + GNUTAR_rdevmajor_offset,
			GNUTAR_rdevmajor_size)) {
			archive_set_error(&a->archive, ERANGE,
			    "Major device number too large");
			ret = ARCHIVE_FAILED;
		}

		if (format_octal(archive_entry_rdevminor(entry),
		    h + GNUTAR_rdevminor_offset,
			GNUTAR_rdevminor_size)) {
			archive_set_error(&a->archive, ERANGE,
			    "Minor device number too large");
			ret = ARCHIVE_FAILED;
		}
	}

	h[GNUTAR_typeflag_offset] = tartype;

	checksum = 0;
	for (i = 0; i < 512; i++)
		checksum += 255 & (unsigned int)h[i];
	h[GNUTAR_checksum_offset + 6] = '\0'; /* Can't be pre-set in the template. */
	/* h[GNUTAR_checksum_offset + 7] = ' '; */ /* This is pre-set in the template. */
	format_octal(checksum, h + GNUTAR_checksum_offset, 6);
	return (ret);
}