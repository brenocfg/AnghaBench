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
typedef  scalar_t__ uint64_t ;
struct heap_queue {int used; int allocated; struct file_info** files; } ;
struct file_info {scalar_t__ key; } ;
struct archive_read {int /*<<< orphan*/  archive; } ;
typedef  int /*<<< orphan*/  new_pending_files ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct file_info**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (struct file_info**,struct file_info**,int) ; 

__attribute__((used)) static int
heap_add_entry(struct archive_read *a, struct heap_queue *heap,
    struct file_info *file, uint64_t key)
{
	uint64_t file_key, parent_key;
	int hole, parent;

	/* Expand our pending files list as necessary. */
	if (heap->used >= heap->allocated) {
		struct file_info **new_pending_files;
		int new_size = heap->allocated * 2;

		if (heap->allocated < 1024)
			new_size = 1024;
		/* Overflow might keep us from growing the list. */
		if (new_size <= heap->allocated) {
			archive_set_error(&a->archive,
			    ENOMEM, "Out of memory");
			return (ARCHIVE_FATAL);
		}
		new_pending_files = (struct file_info **)
		    malloc(new_size * sizeof(new_pending_files[0]));
		if (new_pending_files == NULL) {
			archive_set_error(&a->archive,
			    ENOMEM, "Out of memory");
			return (ARCHIVE_FATAL);
		}
		if (heap->allocated)
			memcpy(new_pending_files, heap->files,
			    heap->allocated * sizeof(new_pending_files[0]));
		free(heap->files);
		heap->files = new_pending_files;
		heap->allocated = new_size;
	}

	file_key = file->key = key;

	/*
	 * Start with hole at end, walk it up tree to find insertion point.
	 */
	hole = heap->used++;
	while (hole > 0) {
		parent = (hole - 1)/2;
		parent_key = heap->files[parent]->key;
		if (file_key >= parent_key) {
			heap->files[hole] = file;
			return (ARCHIVE_OK);
		}
		/* Move parent into hole <==> move hole up tree. */
		heap->files[hole] = heap->files[parent];
		hole = parent;
	}
	heap->files[0] = file;

	return (ARCHIVE_OK);
}