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
struct archive_read_filter {int closed; int (* close ) (struct archive_read_filter*) ;int /*<<< orphan*/ * buffer; struct archive_read_filter* upstream; } ;
struct archive_read {struct archive_read_filter* filter; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int stub1 (struct archive_read_filter*) ; 

__attribute__((used)) static int
close_filters(struct archive_read *a)
{
	struct archive_read_filter *f = a->filter;
	int r = ARCHIVE_OK;
	/* Close each filter in the pipeline. */
	while (f != NULL) {
		struct archive_read_filter *t = f->upstream;
		if (!f->closed && f->close != NULL) {
			int r1 = (f->close)(f);
			f->closed = 1;
			if (r1 < r)
				r = r1;
		}
		free(f->buffer);
		f->buffer = NULL;
		f = t;
	}
	return r;
}