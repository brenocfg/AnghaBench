#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int state; } ;
struct archive_write {int (* format_write_header ) (struct archive_write*,struct archive_entry*) ;scalar_t__ skip_file_ino; TYPE_1__ archive; scalar_t__ skip_file_dev; scalar_t__ skip_file_set; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;
typedef  scalar_t__ dev_t ;

/* Variables and functions */
 int ARCHIVE_FAILED ; 
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_DATA ; 
 void* ARCHIVE_STATE_FATAL ; 
 int ARCHIVE_STATE_HEADER ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  archive_check_magic (TYPE_1__*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_clear_error (TYPE_1__*) ; 
 scalar_t__ archive_entry_dev (struct archive_entry*) ; 
 scalar_t__ archive_entry_dev_is_set (struct archive_entry*) ; 
 scalar_t__ archive_entry_ino64 (struct archive_entry*) ; 
 scalar_t__ archive_entry_ino_is_set (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int,char*) ; 
 int archive_write_finish_entry (TYPE_1__*) ; 
 int stub1 (struct archive_write*,struct archive_entry*) ; 

__attribute__((used)) static int
_archive_write_header(struct archive *_a, struct archive_entry *entry)
{
	struct archive_write *a = (struct archive_write *)_a;
	int ret, r2;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_DATA | ARCHIVE_STATE_HEADER, "archive_write_header");
	archive_clear_error(&a->archive);

	if (a->format_write_header == NULL) {
		archive_set_error(&(a->archive), -1,
		    "Format must be set before you can write to an archive.");
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}

	/* In particular, "retry" and "fatal" get returned immediately. */
	ret = archive_write_finish_entry(&a->archive);
	if (ret == ARCHIVE_FATAL) {
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	if (ret < ARCHIVE_OK && ret != ARCHIVE_WARN)
		return (ret);

	if (a->skip_file_set &&
	    archive_entry_dev_is_set(entry) &&
	    archive_entry_ino_is_set(entry) &&
	    archive_entry_dev(entry) == (dev_t)a->skip_file_dev &&
	    archive_entry_ino64(entry) == a->skip_file_ino) {
		archive_set_error(&a->archive, 0,
		    "Can't add archive to itself");
		return (ARCHIVE_FAILED);
	}

	/* Format and write header. */
	r2 = ((a->format_write_header)(a, entry));
	if (r2 == ARCHIVE_FAILED) {
		return (ARCHIVE_FAILED);
	}
	if (r2 == ARCHIVE_FATAL) {
		a->archive.state = ARCHIVE_STATE_FATAL;
		return (ARCHIVE_FATAL);
	}
	if (r2 < ret)
		ret = r2;

	a->archive.state = ARCHIVE_STATE_DATA;
	return (ret);
}