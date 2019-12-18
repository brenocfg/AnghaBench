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
struct warc_s {unsigned int omit_warcinfo; unsigned int rng; scalar_t__ now; scalar_t__ typ; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; struct warc_s* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_WARC ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  _warc_close ; 
 int /*<<< orphan*/  _warc_data ; 
 int /*<<< orphan*/  _warc_finish_entry ; 
 int /*<<< orphan*/  _warc_free (struct archive_write*) ; 
 int /*<<< orphan*/  _warc_header ; 
 int /*<<< orphan*/  _warc_options ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 struct warc_s* malloc (int) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int
archive_write_set_format_warc(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct warc_s *w;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_set_format_warc");

	/* If another format was already registered, unregister it. */
	if (a->format_free != NULL) {
		(a->format_free)(a);
	}

	w = malloc(sizeof(*w));
	if (w == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate warc data");
		return (ARCHIVE_FATAL);
	}
	/* by default we're emitting a file wide header */
	w->omit_warcinfo = 0U;
	/* obtain current time for date fields */
	w->now = time(NULL);
	/* reset file type info */
	w->typ = 0;
	/* also initialise our rng */
	w->rng = (unsigned int)w->now;

	a->format_data = w;
	a->format_name = "WARC/1.0";
	a->format_options = _warc_options;
	a->format_write_header = _warc_header;
	a->format_write_data = _warc_data;
	a->format_close = _warc_close;
	a->format_free = _warc_free;
	a->format_finish_entry = _warc_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_WARC;
	a->archive.archive_format_name = "WARC/1.0";
	return (ARCHIVE_OK);
}