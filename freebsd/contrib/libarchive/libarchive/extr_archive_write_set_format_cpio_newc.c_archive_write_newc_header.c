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
struct archive_entry {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ENOMEM ; 
 scalar_t__ archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/ * archive_entry_hardlink (struct archive_entry*) ; 
 scalar_t__ archive_entry_pathname_l (struct archive_entry*,char const**,size_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  get_sconv (struct archive_write*) ; 
 int write_header (struct archive_write*,struct archive_entry*) ; 

__attribute__((used)) static int
archive_write_newc_header(struct archive_write *a, struct archive_entry *entry)
{
	const char *path;
	size_t len;

	if (archive_entry_filetype(entry) == 0) {
		archive_set_error(&a->archive, -1, "Filetype required");
		return (ARCHIVE_FAILED);
	}

	if (archive_entry_pathname_l(entry, &path, &len, get_sconv(a)) != 0
	    && errno == ENOMEM) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory for Pathname");
		return (ARCHIVE_FATAL);
	}
	if (len == 0 || path == NULL || path[0] == '\0') {
		archive_set_error(&a->archive, -1, "Pathname required");
		return (ARCHIVE_FAILED);
	}

	if (archive_entry_hardlink(entry) == NULL
	    && (!archive_entry_size_is_set(entry) || archive_entry_size(entry) < 0)) {
		archive_set_error(&a->archive, -1, "Size required");
		return (ARCHIVE_FAILED);
	}
	return write_header(a, entry);
}