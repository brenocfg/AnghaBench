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
struct archive_read_filter {struct archive_read_filter* upstream; } ;
struct archive_read {struct archive_read_filter* filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_filters (struct archive_read*) ; 
 int /*<<< orphan*/  free (struct archive_read_filter*) ; 

void
__archive_read_free_filters(struct archive_read *a)
{
	/* Make sure filters are closed and their buffers are freed */
	close_filters(a);

	while (a->filter != NULL) {
		struct archive_read_filter *t = a->filter->upstream;
		free(a->filter);
		a->filter = t;
	}
}