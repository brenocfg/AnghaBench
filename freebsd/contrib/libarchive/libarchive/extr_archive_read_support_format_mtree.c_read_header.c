#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* s; int length; } ;
struct mtree {int fd; TYPE_3__* this_entry; TYPE_4__ current_dir; int /*<<< orphan*/  archive_format_name; int /*<<< orphan*/  archive_format; int /*<<< orphan*/ * resolver; int /*<<< orphan*/ * entries; } ;
struct TYPE_6__ {int /*<<< orphan*/  archive_format_name; int /*<<< orphan*/  archive_format; } ;
struct archive_read {TYPE_2__ archive; TYPE_1__* format; } ;
struct archive_entry {int dummy; } ;
struct TYPE_7__ {int used; struct TYPE_7__* next; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {scalar_t__ data; } ;

/* Variables and functions */
 int ARCHIVE_EOF ; 
 int ARCHIVE_FATAL ; 
 int /*<<< orphan*/  ARCHIVE_FORMAT_MTREE ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/ * archive_entry_linkresolver_new () ; 
 int /*<<< orphan*/  archive_entry_linkresolver_set_strategy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ archive_strlen (TYPE_4__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int parse_file (struct archive_read*,struct archive_entry*,struct mtree*,TYPE_3__*,int*) ; 
 int read_mtree (struct archive_read*,struct mtree*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
read_header(struct archive_read *a, struct archive_entry *entry)
{
	struct mtree *mtree;
	char *p;
	int r, use_next;

	mtree = (struct mtree *)(a->format->data);

	if (mtree->fd >= 0) {
		close(mtree->fd);
		mtree->fd = -1;
	}

	if (mtree->entries == NULL) {
		mtree->resolver = archive_entry_linkresolver_new();
		if (mtree->resolver == NULL)
			return ARCHIVE_FATAL;
		archive_entry_linkresolver_set_strategy(mtree->resolver,
		    ARCHIVE_FORMAT_MTREE);
		r = read_mtree(a, mtree);
		if (r != ARCHIVE_OK)
			return (r);
	}

	a->archive.archive_format = mtree->archive_format;
	a->archive.archive_format_name = mtree->archive_format_name;

	for (;;) {
		if (mtree->this_entry == NULL)
			return (ARCHIVE_EOF);
		if (strcmp(mtree->this_entry->name, "..") == 0) {
			mtree->this_entry->used = 1;
			if (archive_strlen(&mtree->current_dir) > 0) {
				/* Roll back current path. */
				p = mtree->current_dir.s
				    + mtree->current_dir.length - 1;
				while (p >= mtree->current_dir.s && *p != '/')
					--p;
				if (p >= mtree->current_dir.s)
					--p;
				mtree->current_dir.length
				    = p - mtree->current_dir.s + 1;
			}
		}
		if (!mtree->this_entry->used) {
			use_next = 0;
			r = parse_file(a, entry, mtree, mtree->this_entry,
				&use_next);
			if (use_next == 0)
				return (r);
		}
		mtree->this_entry = mtree->this_entry->next;
	}
}