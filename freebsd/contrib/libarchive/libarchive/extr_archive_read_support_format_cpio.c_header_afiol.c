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
struct cpio {scalar_t__ entry_padding; scalar_t__ entry_bytes_remaining; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_1__ archive; } ;
struct archive_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_CPIO_AFIO_LARGE ; 
 int ARCHIVE_OK ; 
 void* __archive_read_ahead (struct archive_read*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __archive_read_consume (struct archive_read*,int /*<<< orphan*/ ) ; 
 int afiol_dev_offset ; 
 int /*<<< orphan*/  afiol_dev_size ; 
 int afiol_filesize_offset ; 
 int /*<<< orphan*/  afiol_filesize_size ; 
 int afiol_gid_offset ; 
 int /*<<< orphan*/  afiol_gid_size ; 
 int /*<<< orphan*/  afiol_header_size ; 
 int afiol_ino_offset ; 
 int /*<<< orphan*/  afiol_ino_size ; 
 int afiol_mode_offset ; 
 int /*<<< orphan*/  afiol_mode_size ; 
 int afiol_mtime_offset ; 
 int /*<<< orphan*/  afiol_mtime_size ; 
 int afiol_namesize_offset ; 
 int /*<<< orphan*/  afiol_namesize_size ; 
 int afiol_nlink_offset ; 
 int /*<<< orphan*/  afiol_nlink_size ; 
 int afiol_rdev_offset ; 
 int /*<<< orphan*/  afiol_rdev_size ; 
 int afiol_uid_offset ; 
 int /*<<< orphan*/  afiol_uid_size ; 
 int /*<<< orphan*/  archive_entry_set_dev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_gid (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_ino (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_mode (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_mtime (struct archive_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_nlink (struct archive_entry*,unsigned int) ; 
 int /*<<< orphan*/  archive_entry_set_rdev (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_size (struct archive_entry*,scalar_t__) ; 
 int /*<<< orphan*/  archive_entry_set_uid (struct archive_entry*,scalar_t__) ; 
 scalar_t__ atol16 (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ atol8 (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
header_afiol(struct archive_read *a, struct cpio *cpio,
    struct archive_entry *entry, size_t *namelength, size_t *name_pad)
{
	const void *h;
	const char *header;

	a->archive.archive_format = ARCHIVE_FORMAT_CPIO_AFIO_LARGE;
	a->archive.archive_format_name = "afio large ASCII";

	/* Read fixed-size portion of header. */
	h = __archive_read_ahead(a, afiol_header_size, NULL);
	if (h == NULL)
	    return (ARCHIVE_FATAL);

	/* Parse out octal fields. */
	header = (const char *)h;

	archive_entry_set_dev(entry, 
		(dev_t)atol16(header + afiol_dev_offset, afiol_dev_size));
	archive_entry_set_ino(entry, atol16(header + afiol_ino_offset, afiol_ino_size));
	archive_entry_set_mode(entry,
		(mode_t)atol8(header + afiol_mode_offset, afiol_mode_size));
	archive_entry_set_uid(entry, atol16(header + afiol_uid_offset, afiol_uid_size));
	archive_entry_set_gid(entry, atol16(header + afiol_gid_offset, afiol_gid_size));
	archive_entry_set_nlink(entry,
		(unsigned int)atol16(header + afiol_nlink_offset, afiol_nlink_size));
	archive_entry_set_rdev(entry,
		(dev_t)atol16(header + afiol_rdev_offset, afiol_rdev_size));
	archive_entry_set_mtime(entry, atol16(header + afiol_mtime_offset, afiol_mtime_size), 0);
	*namelength = (size_t)atol16(header + afiol_namesize_offset, afiol_namesize_size);
	*name_pad = 0; /* No padding of filename. */

	cpio->entry_bytes_remaining =
	    atol16(header + afiol_filesize_offset, afiol_filesize_size);
	archive_entry_set_size(entry, cpio->entry_bytes_remaining);
	cpio->entry_padding = 0;
	__archive_read_consume(a, afiol_header_size);
	return (ARCHIVE_OK);
}