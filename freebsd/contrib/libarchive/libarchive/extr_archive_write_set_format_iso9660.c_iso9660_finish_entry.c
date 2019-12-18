#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ making; } ;
struct iso9660 {scalar_t__ bytes_remaining; TYPE_4__* cur_file; TYPE_2__ zisofs; } ;
struct archive_write {size_t null_length; int /*<<< orphan*/  nulls; struct iso9660* format_data; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_8__ {TYPE_3__* cur_content; TYPE_1__ content; int /*<<< orphan*/  entry; } ;
struct TYPE_7__ {int size; int blocks; } ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int LOGICAL_BLOCK_BITS ; 
 int LOGICAL_BLOCK_SIZE ; 
 scalar_t__ archive_entry_filetype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isofile_add_data_file (struct iso9660*,TYPE_4__*) ; 
 int wb_write_padding_to_temp (struct archive_write*,int) ; 
 scalar_t__ write_iso9660_data (struct archive_write*,int /*<<< orphan*/ ,size_t) ; 
 int zisofs_finish_entry (struct archive_write*) ; 

__attribute__((used)) static int
iso9660_finish_entry(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;

	if (iso9660->cur_file == NULL)
		return (ARCHIVE_OK);
	if (archive_entry_filetype(iso9660->cur_file->entry) != AE_IFREG)
		return (ARCHIVE_OK);
	if (iso9660->cur_file->content.size == 0)
		return (ARCHIVE_OK);

	/* If there are unwritten data, write null data instead. */
	while (iso9660->bytes_remaining > 0) {
		size_t s;

		s = (iso9660->bytes_remaining > a->null_length)?
		    a->null_length: (size_t)iso9660->bytes_remaining;
		if (write_iso9660_data(a, a->nulls, s) < 0)
			return (ARCHIVE_FATAL);
		iso9660->bytes_remaining -= s;
	}

	if (iso9660->zisofs.making && zisofs_finish_entry(a) != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Write padding. */
	if (wb_write_padding_to_temp(a, iso9660->cur_file->cur_content->size)
	    != ARCHIVE_OK)
		return (ARCHIVE_FATAL);

	/* Compute the logical block number. */
	iso9660->cur_file->cur_content->blocks = (int)
	    ((iso9660->cur_file->cur_content->size
	     + LOGICAL_BLOCK_SIZE -1) >> LOGICAL_BLOCK_BITS);

	/* Add the current file to data file list. */
	isofile_add_data_file(iso9660, iso9660->cur_file);

	return (ARCHIVE_OK);
}