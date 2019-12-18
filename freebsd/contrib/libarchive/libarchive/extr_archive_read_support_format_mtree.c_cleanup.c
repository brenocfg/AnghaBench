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
struct mtree_entry {struct mtree_entry* buff; int /*<<< orphan*/  resolver; int /*<<< orphan*/  contents_name; int /*<<< orphan*/  current_dir; int /*<<< orphan*/  line; int /*<<< orphan*/  options; struct mtree_entry* name; struct mtree_entry* next; struct mtree_entry* entries; } ;
struct mtree {struct mtree* buff; int /*<<< orphan*/  resolver; int /*<<< orphan*/  contents_name; int /*<<< orphan*/  current_dir; int /*<<< orphan*/  line; int /*<<< orphan*/  options; struct mtree* name; struct mtree* next; struct mtree* entries; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  archive_entry_linkresolver_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_string_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mtree_entry*) ; 
 int /*<<< orphan*/  free_options (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cleanup(struct archive_read *a)
{
	struct mtree *mtree;
	struct mtree_entry *p, *q;

	mtree = (struct mtree *)(a->format->data);

	p = mtree->entries;
	while (p != NULL) {
		q = p->next;
		free(p->name);
		free_options(p->options);
		free(p);
		p = q;
	}
	archive_string_free(&mtree->line);
	archive_string_free(&mtree->current_dir);
	archive_string_free(&mtree->contents_name);
	archive_entry_linkresolver_free(mtree->resolver);

	free(mtree->buff);
	free(mtree);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}