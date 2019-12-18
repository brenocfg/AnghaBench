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
struct creation_set {int filter_count; TYPE_1__* filters; } ;
struct archive {int dummy; } ;
struct TYPE_2__ {void* filter_name; scalar_t__ program; } ;

/* Variables and functions */
 int ARCHIVE_WARN ; 
 int archive_write_add_filter_by_name (struct archive*,void*) ; 
 int archive_write_add_filter_program (struct archive*,void*) ; 

int
cset_write_add_filters(struct creation_set *cset, struct archive *a,
    const void **filter_name)
{
	int cnt = 0, i, r;

	for (i = 0; i < cset->filter_count; i++) {
		if (cset->filters[i].program)
			r = archive_write_add_filter_program(a,
				cset->filters[i].filter_name);
		else
			r = archive_write_add_filter_by_name(a,
				cset->filters[i].filter_name);
		if (r < ARCHIVE_WARN) {
			*filter_name = cset->filters[i].filter_name;
			return (r);
		}
		++cnt;
	}
	return (cnt);
}