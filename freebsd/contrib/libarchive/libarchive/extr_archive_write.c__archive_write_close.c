#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int state; } ;
struct archive_write {int (* format_finish_entry ) (struct archive_write*) ;int (* format_close ) (struct archive_write*) ;TYPE_1__ archive; int /*<<< orphan*/  filter_first; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_STATE_ANY ; 
 int ARCHIVE_STATE_CLOSED ; 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_FATAL ; 
 int ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int __archive_write_close_filter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_check_magic (TYPE_1__*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_clear_error (TYPE_1__*) ; 
 int stub1 (struct archive_write*) ; 
 int stub2 (struct archive_write*) ; 

__attribute__((used)) static int
_archive_write_close(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	int r = ARCHIVE_OK, r1 = ARCHIVE_OK;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL,
	    "archive_write_close");
	if (a->archive.state == ARCHIVE_STATE_NEW
	    || a->archive.state == ARCHIVE_STATE_CLOSED)
		return (ARCHIVE_OK); /* Okay to close() when not open. */

	archive_clear_error(&a->archive);

	/* Finish the last entry if a finish callback is specified */
	if (a->archive.state == ARCHIVE_STATE_DATA
	    && a->format_finish_entry != NULL)
		r = ((a->format_finish_entry)(a));

	/* Finish off the archive. */
	/* TODO: have format closers invoke compression close. */
	if (a->format_close != NULL) {
		r1 = (a->format_close)(a);
		if (r1 < r)
			r = r1;
	}

	/* Finish the compression and close the stream. */
	r1 = __archive_write_close_filter(a->filter_first);
	if (r1 < r)
		r = r1;

	if (a->archive.state != ARCHIVE_STATE_FATAL)
		a->archive.state = ARCHIVE_STATE_CLOSED;
	return (r);
}