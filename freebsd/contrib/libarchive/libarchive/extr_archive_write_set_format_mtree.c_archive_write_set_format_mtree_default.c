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
struct mtree_writer {int first; int /*<<< orphan*/  buf; int /*<<< orphan*/  ebuf; scalar_t__ indent; scalar_t__ dironly; int /*<<< orphan*/  keys; int /*<<< orphan*/  set; int /*<<< orphan*/ * mtree_entry; } ;
struct TYPE_2__ {char* archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_write {char* format_name; TYPE_1__ archive; int /*<<< orphan*/  format_finish_entry; int /*<<< orphan*/  format_write_data; int /*<<< orphan*/  format_close; int /*<<< orphan*/  format_write_header; int /*<<< orphan*/  format_options; int /*<<< orphan*/  (* format_free ) (struct archive_write*) ;struct mtree_writer* format_data; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_MTREE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_NEW ; 
 int /*<<< orphan*/  ARCHIVE_WRITE_MAGIC ; 
 int /*<<< orphan*/  DEFAULT_KEYS ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_check_magic (struct archive*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  archive_string_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  archive_write_mtree_close ; 
 int /*<<< orphan*/  archive_write_mtree_data ; 
 int /*<<< orphan*/  archive_write_mtree_finish_entry ; 
 int /*<<< orphan*/  archive_write_mtree_free (struct archive_write*) ; 
 int /*<<< orphan*/  archive_write_mtree_header ; 
 int /*<<< orphan*/  archive_write_mtree_options ; 
 struct mtree_writer* calloc (int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtree_entry_register_init (struct mtree_writer*) ; 
 int /*<<< orphan*/  stub1 (struct archive_write*) ; 

__attribute__((used)) static int
archive_write_set_format_mtree_default(struct archive *_a, const char *fn)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct mtree_writer *mtree;

	archive_check_magic(_a, ARCHIVE_WRITE_MAGIC, ARCHIVE_STATE_NEW, fn);

	if (a->format_free != NULL)
		(a->format_free)(a);

	if ((mtree = calloc(1, sizeof(*mtree))) == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate mtree data");
		return (ARCHIVE_FATAL);
	}

	mtree->mtree_entry = NULL;
	mtree->first = 1;
	memset(&(mtree->set), 0, sizeof(mtree->set));
	mtree->keys = DEFAULT_KEYS;
	mtree->dironly = 0;
	mtree->indent = 0;
	archive_string_init(&mtree->ebuf);
	archive_string_init(&mtree->buf);
	mtree_entry_register_init(mtree);
	a->format_data = mtree;
	a->format_free = archive_write_mtree_free;
	a->format_name = "mtree";
	a->format_options = archive_write_mtree_options;
	a->format_write_header = archive_write_mtree_header;
	a->format_close = archive_write_mtree_close;
	a->format_write_data = archive_write_mtree_data;
	a->format_finish_entry = archive_write_mtree_finish_entry;
	a->archive.archive_format = ARCHIVE_FORMAT_MTREE;
	a->archive.archive_format_name = "mtree";

	return (ARCHIVE_OK);
}