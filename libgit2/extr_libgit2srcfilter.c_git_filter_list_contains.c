#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; TYPE_1__* ptr; } ;
struct TYPE_7__ {TYPE_2__ filters; } ;
typedef  TYPE_3__ git_filter_list ;
struct TYPE_5__ {int /*<<< orphan*/  filter_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

int git_filter_list_contains(
	git_filter_list *fl,
	const char *name)
{
	size_t i;

	assert(name);

	if (!fl)
		return 0;

	for (i = 0; i < fl->filters.size; i++) {
		if (strcmp(fl->filters.ptr[i].filter_name, name) == 0)
			return 1;
	}

	return 0;
}