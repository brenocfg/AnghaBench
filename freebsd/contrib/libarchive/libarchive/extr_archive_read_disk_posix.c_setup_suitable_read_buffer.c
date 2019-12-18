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
struct tree {struct filesystem* current_filesystem; } ;
struct filesystem {int xfer_align; int max_xfer_size; long incr_xfer_size; long min_xfer_size; size_t buff_size; int /*<<< orphan*/ * allocation_ptr; int /*<<< orphan*/ * buff; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct archive_read_disk {TYPE_1__ archive; struct tree* tree; } ;

/* Variables and functions */
 int ARCHIVE_FATAL ; 
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  ARCHIVE_STATE_FATAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  archive_set_error (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 

__attribute__((used)) static int
setup_suitable_read_buffer(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
	struct filesystem *cf = t->current_filesystem;
	size_t asize;
	size_t s;

	if (cf->allocation_ptr == NULL) {
		/* If we couldn't get a filesystem alignment,
		 * we use 4096 as default value but we won't use
		 * O_DIRECT to open() and openat() operations. */
		long xfer_align = (cf->xfer_align == -1)?4096:cf->xfer_align;

		if (cf->max_xfer_size != -1)
			asize = cf->max_xfer_size + xfer_align;
		else {
			long incr = cf->incr_xfer_size;
			/* Some platform does not set a proper value to
			 * incr_xfer_size.*/
			if (incr < 0)
				incr = cf->min_xfer_size;
			if (cf->min_xfer_size < 0) {
				incr = xfer_align;
				asize = xfer_align;
			} else
				asize = cf->min_xfer_size;

			/* Increase a buffer size up to 64K bytes in
			 * a proper increment size. */
			while (asize < 1024*64)
				asize += incr;
			/* Take a margin to adjust to the filesystem
			 * alignment. */
			asize += xfer_align;
		}
		cf->allocation_ptr = malloc(asize);
		if (cf->allocation_ptr == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Couldn't allocate memory");
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		}

		/*
		 * Calculate proper address for the filesystem.
		 */
		s = (uintptr_t)cf->allocation_ptr;
		s %= xfer_align;
		if (s > 0)
			s = xfer_align - s;

		/*
		 * Set a read buffer pointer in the proper alignment of
		 * the current filesystem.
		 */
		cf->buff = cf->allocation_ptr + s;
		cf->buff_size = asize - xfer_align;
	}
	return (ARCHIVE_OK);
}