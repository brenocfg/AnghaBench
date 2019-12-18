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
struct tree {int max_filesystem_id; int current_filesystem_id; size_t allocated_filesystem; struct filesystem* current_filesystem; struct filesystem* filesystem_table; } ;
struct filesystem {scalar_t__ dev; int /*<<< orphan*/ * buff; int /*<<< orphan*/ * allocation_ptr; } ;
struct archive_read_disk {int /*<<< orphan*/  archive; struct tree* tree; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 void* realloc (struct filesystem*,size_t) ; 
 int setup_current_filesystem (struct archive_read_disk*) ; 

__attribute__((used)) static int
update_current_filesystem(struct archive_read_disk *a, int64_t dev)
{
	struct tree *t = a->tree;
	int i, fid;

	if (t->current_filesystem != NULL &&
	    t->current_filesystem->dev == dev)
		return (ARCHIVE_OK);

	for (i = 0; i < t->max_filesystem_id; i++) {
		if (t->filesystem_table[i].dev == dev) {
			/* There is the filesystem ID we've already generated. */
			t->current_filesystem_id = i;
			t->current_filesystem = &(t->filesystem_table[i]);
			return (ARCHIVE_OK);
		}
	}

	/*
	 * This is the new filesystem which we have to generate a new ID for.
	 */
	fid = t->max_filesystem_id++;
	if (t->max_filesystem_id > t->allocated_filesystem) {
		size_t s;
		void *p;

		s = t->max_filesystem_id * 2;
		p = realloc(t->filesystem_table,
		        s * sizeof(*t->filesystem_table));
		if (p == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate tar data");
			return (ARCHIVE_FATAL);
		}
		t->filesystem_table = (struct filesystem *)p;
		t->allocated_filesystem = s;
	}
	t->current_filesystem_id = fid;
	t->current_filesystem = &(t->filesystem_table[fid]);
	t->current_filesystem->dev = dev;
	t->current_filesystem->allocation_ptr = NULL;
	t->current_filesystem->buff = NULL;

	/* Setup the current filesystem properties which depend on
	 * platform specific. */
	return (setup_current_filesystem(a));
}