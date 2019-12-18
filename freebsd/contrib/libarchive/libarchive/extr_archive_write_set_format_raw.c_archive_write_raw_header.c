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
struct raw {scalar_t__ entries_written; } ;
struct archive_write {int /*<<< orphan*/  archive; scalar_t__ format_data; } ;
struct archive_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ AE_IFREG ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ERANGE ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
archive_write_raw_header(struct archive_write *a, struct archive_entry *entry)
{
	struct raw *raw = (struct raw *)a->format_data;

	if (archive_entry_filetype(entry) != AE_IFREG) {
		archive_set_error(&a->archive, ERANGE,
		    "Raw format only supports filetype AE_IFREG");
		return (ARCHIVE_FATAL);
	}


	if (raw->entries_written > 0) {
		archive_set_error(&a->archive, ERANGE,
		    "Raw format only supports one entry per archive");
		return (ARCHIVE_FATAL);
	}
	raw->entries_written++;

	return (ARCHIVE_OK);
}