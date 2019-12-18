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
struct list_objects_filter_options {int sub_nr; int /*<<< orphan*/ * sub; } ;
struct filter {int /*<<< orphan*/  finalize_omits_fn; int /*<<< orphan*/  free_fn; int /*<<< orphan*/  filter_object_fn; struct combine_filter_data* filter_data; scalar_t__ omits; } ;
struct combine_filter_data {int nr; TYPE_1__* sub; } ;
struct TYPE_2__ {int /*<<< orphan*/  omits; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_combine ; 
 int /*<<< orphan*/  filter_combine__finalize_omits ; 
 int /*<<< orphan*/  filter_combine__free ; 
 int /*<<< orphan*/  list_objects_filter__init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static void filter_combine__init(
	struct list_objects_filter_options *filter_options,
	struct filter* filter)
{
	struct combine_filter_data *d = xcalloc(1, sizeof(*d));
	size_t sub;

	d->nr = filter_options->sub_nr;
	d->sub = xcalloc(d->nr, sizeof(*d->sub));
	for (sub = 0; sub < d->nr; sub++)
		d->sub[sub].filter = list_objects_filter__init(
			filter->omits ? &d->sub[sub].omits : NULL,
			&filter_options->sub[sub]);

	filter->filter_data = d;
	filter->filter_object_fn = filter_combine;
	filter->free_fn = filter_combine__free;
	filter->finalize_omits_fn = filter_combine__finalize_omits;
}