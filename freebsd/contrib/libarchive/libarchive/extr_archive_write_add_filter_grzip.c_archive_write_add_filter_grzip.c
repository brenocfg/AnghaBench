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
struct write_grzip {int /*<<< orphan*/ * pdata; } ;
struct archive_write_filter {char* name; int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  write; int /*<<< orphan*/  options; int /*<<< orphan*/  open; struct write_grzip* data; int /*<<< orphan*/  code; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE_ERRNO_MISC ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_GRZIP ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int ARCHIVE_WARN ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct archive_write_filter* __archive_write_allocate_filter (struct archive*) ; 
 int /*<<< orphan*/ * __archive_write_program_allocate (char*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_set_error (struct archive*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_write_grzip_close ; 
 int /*<<< orphan*/  archive_write_grzip_free ; 
 int /*<<< orphan*/  archive_write_grzip_open ; 
 int /*<<< orphan*/  archive_write_grzip_options ; 
 int /*<<< orphan*/  archive_write_grzip_write ; 
 struct write_grzip* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct write_grzip*) ; 

int
archive_write_add_filter_grzip(struct archive *_a)
{
	struct archive_write_filter *f = __archive_write_allocate_filter(_a);
	struct write_grzip *data;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_add_filter_grzip");

	data = calloc(1, sizeof(*data));
	if (data == NULL) {
		archive_set_error(_a, ENOMEM, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	data->pdata = __archive_write_program_allocate("grzip");
	if (data->pdata == NULL) {
		free(data);
		archive_set_error(_a, ENOMEM, "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}

	f->name = "grzip";
	f->code = ARCHIVE_FILTER_GRZIP;
	f->data = data;
	f->open = archive_write_grzip_open;
	f->options = archive_write_grzip_options;
	f->write = archive_write_grzip_write;
	f->close = archive_write_grzip_close;
	f->free = archive_write_grzip_free;

	/* Note: This filter always uses an external program, so we
	 * return "warn" to inform of the fact. */
	archive_set_error(_a, ARCHIVE_ERRNO_MISC,
	    "Using external grzip program for grzip compression");
	return (ARCHIVE_WARN);
}