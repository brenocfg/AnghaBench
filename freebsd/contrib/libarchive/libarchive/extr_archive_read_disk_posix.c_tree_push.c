#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  noatime; int /*<<< orphan*/  filetype; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  s; } ;
struct tree_entry {int symlink_parent_fd; int flags; int filesystem_id; TYPE_2__ restore_time; TYPE_3__ name; int /*<<< orphan*/  dirname_length; void* ino; void* dev; TYPE_1__* parent; scalar_t__ depth; struct tree_entry* next; } ;
struct tree {int /*<<< orphan*/  dirname_length; struct tree_entry* stack; TYPE_1__* current; } ;
struct restore_time {int /*<<< orphan*/  noatime; int /*<<< orphan*/  filetype; int /*<<< orphan*/  atime_nsec; int /*<<< orphan*/  atime; int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime; } ;
typedef  void* int64_t ;
struct TYPE_5__ {scalar_t__ depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_strcpy (TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  archive_string_init (TYPE_3__*) ; 
 struct tree_entry* calloc (int,int) ; 
 int needsAscent ; 
 int needsDescent ; 
 int needsOpen ; 

__attribute__((used)) static void
tree_push(struct tree *t, const char *path, int filesystem_id,
    int64_t dev, int64_t ino, struct restore_time *rt)
{
	struct tree_entry *te;

	te = calloc(1, sizeof(*te));
	te->next = t->stack;
	te->parent = t->current;
	if (te->parent)
		te->depth = te->parent->depth + 1;
	t->stack = te;
	archive_string_init(&te->name);
	te->symlink_parent_fd = -1;
	archive_strcpy(&te->name, path);
	te->flags = needsDescent | needsOpen | needsAscent;
	te->filesystem_id = filesystem_id;
	te->dev = dev;
	te->ino = ino;
	te->dirname_length = t->dirname_length;
	te->restore_time.name = te->name.s;
	if (rt != NULL) {
		te->restore_time.mtime = rt->mtime;
		te->restore_time.mtime_nsec = rt->mtime_nsec;
		te->restore_time.atime = rt->atime;
		te->restore_time.atime_nsec = rt->atime_nsec;
		te->restore_time.filetype = rt->filetype;
		te->restore_time.noatime = rt->noatime;
	}
}