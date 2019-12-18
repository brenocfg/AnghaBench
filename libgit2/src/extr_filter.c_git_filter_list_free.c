#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  filters; } ;
typedef  TYPE_1__ git_filter_list ;
struct TYPE_8__ {int /*<<< orphan*/  payload; TYPE_3__* filter; } ;
typedef  TYPE_2__ git_filter_entry ;
struct TYPE_9__ {int /*<<< orphan*/  (* cleanup ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_array_clear (int /*<<< orphan*/ ) ; 
 TYPE_2__* git_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ git_array_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

void git_filter_list_free(git_filter_list *fl)
{
	uint32_t i;

	if (!fl)
		return;

	for (i = 0; i < git_array_size(fl->filters); ++i) {
		git_filter_entry *fe = git_array_get(fl->filters, i);
		if (fe->filter->cleanup)
			fe->filter->cleanup(fe->filter, fe->payload);
	}

	git_array_clear(fl->filters);
	git__free(fl);
}