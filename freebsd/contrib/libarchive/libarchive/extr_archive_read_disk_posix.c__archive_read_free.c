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
struct TYPE_3__ {scalar_t__ state; scalar_t__ magic; int /*<<< orphan*/  error_string; } ;
struct archive_read_disk {TYPE_1__ archive; int /*<<< orphan*/  entry; int /*<<< orphan*/ * lookup_uname_data; int /*<<< orphan*/  (* cleanup_uname ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/ * lookup_gname_data; int /*<<< orphan*/  (* cleanup_gname ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  tree; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_READ_DISK_MAGIC ; 
 int ARCHIVE_STATE_ANY ; 
 scalar_t__ ARCHIVE_STATE_CLOSED ; 
 int ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  __archive_clean (TYPE_1__*) ; 
 int _archive_read_close (TYPE_1__*) ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  archive_entry_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct archive_read_disk*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_archive_read_free(struct archive *_a)
{
	struct archive_read_disk *a = (struct archive_read_disk *)_a;
	int r;

	if (_a == NULL)
		return (ARCHIVE_OK);
	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,
	    ARCHIVE_STATE_ANY | ARCHIVE_STATE_FATAL, "archive_read_free");

	if (a->archive.state != ARCHIVE_STATE_CLOSED)
		r = _archive_read_close(&a->archive);
	else
		r = ARCHIVE_OK;

	tree_free(a->tree);
	if (a->cleanup_gname != NULL && a->lookup_gname_data != NULL)
		(a->cleanup_gname)(a->lookup_gname_data);
	if (a->cleanup_uname != NULL && a->lookup_uname_data != NULL)
		(a->cleanup_uname)(a->lookup_uname_data);
	archive_string_free(&a->archive.error_string);
	archive_entry_free(a->entry);
	a->archive.magic = 0;
	__archive_clean(&a->archive);
	free(a);
	return (r);
}