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
struct tree {int entry_fd; int entry_eof; int /*<<< orphan*/  entry_remaining_bytes; int /*<<< orphan*/  nlink; int /*<<< orphan*/  entry_total; int /*<<< orphan*/  restore_time; } ;
struct TYPE_2__ {int state; } ;
struct archive_read_disk {TYPE_1__ archive; struct tree* tree; } ;
struct archive_entry {int dummy; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AE_IFREG ; 
#define  ARCHIVE_EOF 132 
#define  ARCHIVE_FATAL 131 
#define  ARCHIVE_OK 130 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
#define  ARCHIVE_RETRY 129 
 int ARCHIVE_STATE_DATA ; 
 int ARCHIVE_STATE_EOF ; 
 int ARCHIVE_STATE_FATAL ; 
 int ARCHIVE_STATE_HEADER ; 
#define  ARCHIVE_WARN 128 
 int /*<<< orphan*/  __archive_reset_read_data (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_entry_clear (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_copy_sourcepath (struct archive_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_entry_filetype (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_nlink (struct archive_entry*) ; 
 int /*<<< orphan*/  archive_entry_size (struct archive_entry*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  close_and_restore_time (int,struct tree*,int /*<<< orphan*/ *) ; 
 int next_entry (struct archive_read_disk*,struct tree*,struct archive_entry*) ; 
 int const setup_sparse (struct archive_read_disk*,struct archive_entry*) ; 
 int /*<<< orphan*/  tree_current_path (struct tree*) ; 
 int /*<<< orphan*/  tree_enter_initial_dir (struct tree*) ; 

__attribute__((used)) static int
_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	struct tree *t;
	int r;

	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,
	    "archive_read_next_header2");

	t = a->tree;
	if (t->entry_fd >= 0) {
		close_and_restore_time(t->entry_fd, t, &t->restore_time);
		t->entry_fd = -1;
	}

	archive_entry_clear(entry);

	for (;;) {
		r = next_entry(a, t, entry);
		if (t->entry_fd >= 0) {
			close(t->entry_fd);
			t->entry_fd = -1;
		}

		if (r == ARCHIVE_RETRY) {
			archive_entry_clear(entry);
			continue;
		}
		break;
	}

	/* Return to the initial directory. */
	tree_enter_initial_dir(t);

	/*
	 * EOF and FATAL are persistent at this layer.  By
	 * modifying the state, we guarantee that future calls to
	 * read a header or read data will fail.
	 */
	switch (r) {
	case ARCHIVE_EOF:
		a->archive.state = ARCHIVE_STATE_EOF;
		break;
	case ARCHIVE_OK:
	case ARCHIVE_WARN:
		/* Overwrite the sourcepath based on the initial directory. */
		archive_entry_copy_sourcepath(entry, tree_current_path(t));
		t->entry_total = 0;
		if (archive_entry_filetype(entry) == AE_IFREG) {
			t->nlink = archive_entry_nlink(entry);
			t->entry_remaining_bytes = archive_entry_size(entry);
			t->entry_eof = (t->entry_remaining_bytes == 0)? 1: 0;
			if (!t->entry_eof &&
			    setup_sparse(a, entry) != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
		} else {
			t->entry_remaining_bytes = 0;
			t->entry_eof = 1;
		}
		a->archive.state = ARCHIVE_STATE_DATA;
		break;
	case ARCHIVE_RETRY:
		break;
	case ARCHIVE_FATAL:
		a->archive.state = ARCHIVE_STATE_FATAL;
		break;
	}

	__archive_reset_read_data(&a->archive);
	return (r);
}