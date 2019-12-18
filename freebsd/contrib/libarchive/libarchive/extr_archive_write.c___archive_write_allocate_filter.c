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
struct archive_write_filter {struct archive_write_filter* next_filter; struct archive* archive; } ;
struct archive_write {struct archive_write_filter* filter_last; struct archive_write_filter* filter_first; } ;
struct archive {int dummy; } ;

/* Variables and functions */
 struct archive_write_filter* calloc (int,int) ; 

struct archive_write_filter *
__archive_write_allocate_filter(struct archive *_a)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *f;

	f = calloc(1, sizeof(*f));
	f->archive = _a;
	if (a->filter_first == NULL)
		a->filter_first = f;
	else
		a->filter_last->next_filter = f;
	a->filter_last = f;
	return f;
}