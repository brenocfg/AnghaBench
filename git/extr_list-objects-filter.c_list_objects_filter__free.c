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
struct filter {int /*<<< orphan*/  filter_data; int /*<<< orphan*/  (* free_fn ) (int /*<<< orphan*/ ) ;scalar_t__ omits; int /*<<< orphan*/  (* finalize_omits_fn ) (scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct filter*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void list_objects_filter__free(struct filter *filter)
{
	if (!filter)
		return;
	if (filter->finalize_omits_fn && filter->omits)
		filter->finalize_omits_fn(filter->omits, filter->filter_data);
	filter->free_fn(filter->filter_data);
	free(filter);
}