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
struct private_b64encode {int mode; int /*<<< orphan*/  name; } ;
struct archive_write_filter {char* name; int /*<<< orphan*/  free; int /*<<< orphan*/  close; int /*<<< orphan*/  write; int /*<<< orphan*/  options; int /*<<< orphan*/  open; int /*<<< orphan*/  code; struct private_b64encode* data; int /*<<< orphan*/  archive; } ;
struct archive_write {int /*<<< orphan*/  archive; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FILTER_UU ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct archive_write_filter* __archive_write_allocate_filter (struct archive*) ; 
 int /*<<< orphan*/  archive_check_magic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_filter_b64encode_close ; 
 int /*<<< orphan*/  archive_filter_b64encode_free ; 
 int /*<<< orphan*/  archive_filter_b64encode_open ; 
 int /*<<< orphan*/  archive_filter_b64encode_options ; 
 int /*<<< orphan*/  archive_filter_b64encode_write ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_strcpy (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ calloc (int,int) ; 

int
archive_write_add_filter_b64encode(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *f = __archive_write_allocate_filter(_a);
	struct private_b64encode *state;

	archive_check_magic(&a->archive, ARCHIVE_WRITE_MAGIC,
	    ARCHIVE_STATE_NEW, "archive_write_add_filter_uu");

	state = (struct private_b64encode *)calloc(1, sizeof(*state));
	if (state == NULL) {
		archive_set_error(f->archive, ENOMEM,
		    "Can't allocate data for b64encode filter");
		return (ARCHIVE_FATAL);
	}
	archive_strcpy(&state->name, "-");
	state->mode = 0644;

	f->data = state;
	f->name = "b64encode";
	f->code = ARCHIVE_FILTER_UU;
	f->open = archive_filter_b64encode_open;
	f->options = archive_filter_b64encode_options;
	f->write = archive_filter_b64encode_write;
	f->close = archive_filter_b64encode_close;
	f->free = archive_filter_b64encode_free;

	return (ARCHIVE_OK);
}