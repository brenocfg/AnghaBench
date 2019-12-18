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
struct fileblocks {void* buff; scalar_t__ gap_remaining; int fileposition; TYPE_1__* current; } ;
struct archive {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {void* buff; scalar_t__ gap_size; int size; struct TYPE_2__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 void* nulldata ; 
 int nullsize ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static ssize_t
memory_read(struct archive *a, void *_private, const void **buff)
{
	struct fileblocks *private = _private;
	ssize_t size;

	(void)a;

	while (private->current != NULL && private->buff == NULL && private->gap_remaining == 0) {
		private->current = private->current->next;
		if (private->current != NULL) {
			private->buff = private->current->buff;
			private->gap_remaining = private->current->gap_size;
		}
	}

	if (private->current == NULL)
		return (0);

	/* If there's real data, return that. */
	if (private->buff != NULL) {
		*buff = private->buff;
		size = ((char *)private->current->buff + private->current->size)
		    - (char *)private->buff;
		private->buff = NULL;
		private->fileposition += size;
		return (size);
	}

	/* Big gap: too big to return all at once, so just return some. */
	if (private->gap_remaining > (int64_t)nullsize) {
		private->gap_remaining -= nullsize;
		*buff = nulldata;
		private->fileposition += nullsize;
		return (nullsize);
	}

	/* Small gap: finish the gap and prep for next block. */
	if (private->gap_remaining > 0) {
		size = (ssize_t)private->gap_remaining;
		*buff = nulldata;
		private->gap_remaining = 0;
		private->fileposition += size;

		private->current = private->current->next;
		if (private->current != NULL) {
			private->buff = private->current->buff;
			private->gap_remaining = private->current->gap_size;
		}

		return (size);
	}
	fprintf(stderr, "\n\n\nInternal failure\n\n\n");
	exit(1);
}