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
struct tar {int entry_padding; int entry_bytes_remaining; int /*<<< orphan*/  pax_header; } ;
struct archive_read {int dummy; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 
 int err_combine (int,int) ; 
 int pax_header (struct archive_read*,struct tar*,struct archive_entry*,int /*<<< orphan*/ *) ; 
 int read_body_to_string (struct archive_read*,struct tar*,int /*<<< orphan*/ *,void const*,size_t*) ; 
 int tar_read_header (struct archive_read*,struct tar*,struct archive_entry*,size_t*) ; 

__attribute__((used)) static int
header_pax_extensions(struct archive_read *a, struct tar *tar,
    struct archive_entry *entry, const void *h, size_t *unconsumed)
{
	int err, err2;

	err = read_body_to_string(a, tar, &(tar->pax_header), h, unconsumed);
	if (err != ARCHIVE_OK)
		return (err);

	/* Parse the next header. */
	err = tar_read_header(a, tar, entry, unconsumed);
	if ((err != ARCHIVE_OK) && (err != ARCHIVE_WARN))
		return (err);

	/*
	 * TODO: Parse global/default options into 'entry' struct here
	 * before handling file-specific options.
	 *
	 * This design (parse standard header, then overwrite with pax
	 * extended attribute data) usually works well, but isn't ideal;
	 * it would be better to parse the pax extended attributes first
	 * and then skip any fields in the standard header that were
	 * defined in the pax header.
	 */
	err2 = pax_header(a, tar, entry, &tar->pax_header);
	err =  err_combine(err, err2);
	tar->entry_padding = 0x1ff & (-tar->entry_bytes_remaining);
	return (err);
}