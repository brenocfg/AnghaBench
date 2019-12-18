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
struct raw {scalar_t__ entries_written; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/ * format_close; int /*<<< orphan*/ * format_finish_entry; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/ * format_options; struct raw* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_RAW ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_raw_data ; 
 int /*<<< orphan*/  archive_write_raw_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_raw_header ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

int
archive_write_set_format_raw(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct raw *raw;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_raw");

	/* If someone else was already registered, unregister them. */
	if (a->format_free != NULL)
		(a->format_free)(a);

	raw = (struct raw *)calloc(1, sizeof(*raw));
	if (raw == NULL) {
		archive_set_error(&a->archive, ENOMEM, "Can't allocate raw data");
		return (ARCHIVE_FATAL);
	}
	raw->entries_written = 0;
	a->format_data = raw;
	a->format_name = "raw";
        /* no options exist for this format */
	a->format_options = NULL;
	a->format_write_header = archive_write_raw_header;
	a->format_write_data = archive_write_raw_data;
	a->format_finish_entry = NULL;
        /* nothing needs to be done on closing */
	a->format_close = NULL;
	a->format_free = archive_write_raw_free;
	a->archive.archive_format = ARCHIVE_FORMAT_RAW;
	a->archive.archive_format_name = "RAW";
	return (ARCHIVE_OK);
}