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
struct mtree_entry {struct mtree_entry* reg_info; struct mtree_entry* dir_info; int /*<<< orphan*/  fflags_text; int /*<<< orphan*/  gname; int /*<<< orphan*/  uname; int /*<<< orphan*/  symlink; int /*<<< orphan*/  pathname; int /*<<< orphan*/  basename; int /*<<< orphan*/  parentdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mtree_entry*) ; 

__attribute__((used)) static void
mtree_entry_free(struct mtree_entry *me)
{
	archive_string_free(&me->parentdir);
	archive_string_free(&me->basename);
	archive_string_free(&me->pathname);
	archive_string_free(&me->symlink);
	archive_string_free(&me->uname);
	archive_string_free(&me->gname);
	archive_string_free(&me->fflags_text);
	free(me->dir_info);
	free(me->reg_info);
	free(me);
}