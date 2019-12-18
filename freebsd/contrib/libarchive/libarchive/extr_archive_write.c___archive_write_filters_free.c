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
struct archive_write_filter {int (* free ) (struct archive_write_filter*) ;struct archive_write_filter* next_filter; } ;
struct archive_write {int /*<<< orphan*/ * filter_last; struct archive_write_filter* filter_first; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct archive_write_filter*) ; 
 int stub1 (struct archive_write_filter*) ; 

void
__archive_write_filters_free(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	int r = ARCHIVE_OK, r1;

	while (a->filter_first != NULL) {
		struct archive_write_filter *next
		    = a->filter_first->next_filter;
		if (a->filter_first->free != NULL) {
			r1 = (*a->filter_first->free)(a->filter_first);
			if (r > r1)
				r = r1;
		}
		free(a->filter_first);
		a->filter_first = next;
	}
	a->filter_last = NULL;
}