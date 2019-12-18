#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct raw_info {scalar_t__ end_of_file; } ;
struct TYPE_4__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_2__ archive; TYPE_1__* format; } ;
struct archive_entry {int dummy; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFREG ; 
 int ARCHIVE_EOF ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_RAW ; 
 int __archive_read_header (struct archive_read*,struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_set_filetype (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_set_pathname (struct archive_entry*,char*) ; 
 int /*<<< orphan*/  archive_entry_set_perm (struct archive_entry*,int) ; 

__attribute__((used)) static int
archive_read_format_raw_read_header(struct archive_read *a,
    struct archive_entry *entry)
{
	struct raw_info *info;

	info = (struct raw_info *)(a->format->data);
	if (info->end_of_file)
		return (ARCHIVE_EOF);

	a->archive.archive_format = ARCHIVE_FORMAT_RAW;
	a->archive.archive_format_name = "raw";
	archive_entry_set_pathname(entry, "data");
	archive_entry_set_filetype(entry, AE_IFREG);
	archive_entry_set_perm(entry, 0644);
	/* I'm deliberately leaving most fields unset here. */

	/* Let the filter fill out any fields it might have. */
	return __archive_read_header(a, entry);
}