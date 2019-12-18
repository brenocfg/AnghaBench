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
struct TYPE_2__ {int /*<<< orphan*/  filter_name; scalar_t__ program; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_read_support_filter_program (struct archive*,int /*<<< orphan*/ ) ; 

int
cset_read_support_filter_program(struct creation_set *cset, struct archive *a)
{
	int cnt = 0, i;

	for (i = 0; i < cset->filter_count; i++) {
		if (cset->filters[i].program) {
			archive_read_support_filter_program(a,
			    cset->filters[i].filter_name);
			++cnt;
		}
	}
	return (cnt);
}