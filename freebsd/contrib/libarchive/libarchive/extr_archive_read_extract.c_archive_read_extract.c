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
struct archive_read_extract {int /*<<< orphan*/ * ad; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct archive_read_extract* __archive_read_get_extract (struct archive_read*) ; 
 int archive_read_extract2 (int /*<<< orphan*/ *,struct archive_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * archive_write_disk_new () ; 
 int /*<<< orphan*/  archive_write_disk_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  archive_write_disk_set_standard_lookup (int /*<<< orphan*/ *) ; 

int
archive_read_extract(struct archive *_a, struct archive_entry *entry, int flags)
{
	struct archive_read_extract *extract;
	struct archive_read * a = (struct archive_read *)_a;

	extract = __archive_read_get_extract(a);
	if (extract == NULL)
		return (ARCHIVE_FATAL);

	/* If we haven't initialized the archive_write_disk object, do it now. */
	if (extract->ad == NULL) {
		extract->ad = archive_write_disk_new();
		if (extract->ad == NULL) {
			archive_set_error(&a->archive, ENOMEM, "Can't extract");
			return (ARCHIVE_FATAL);
		}
		archive_write_disk_set_standard_lookup(extract->ad);
	}

	archive_write_disk_set_options(extract->ad, flags);
	return (archive_read_extract2(&a->archive, entry, extract->ad));
}