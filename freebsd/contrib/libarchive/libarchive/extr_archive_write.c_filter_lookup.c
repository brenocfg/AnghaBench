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
struct archive_write_filter {struct archive_write_filter* next_filter; } ;
struct archive_write {struct archive_write_filter* filter_last; struct archive_write_filter* filter_first; } ;
struct archive {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static struct archive_write_filter *
filter_lookup(struct archive *_a, int n)
{
	struct archive_write *a = (struct archive_write *)_a;
	struct archive_write_filter *f = a->filter_first;
	if (n == -1)
		return a->filter_last;
	if (n < 0)
		return NULL;
	while (n > 0 && f != NULL) {
		f = f->next_filter;
		--n;
	}
	return f;
}