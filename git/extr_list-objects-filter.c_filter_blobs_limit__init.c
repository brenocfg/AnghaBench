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
struct list_objects_filter_options {int /*<<< orphan*/  blob_limit_value; } ;
struct filter_blobs_limit_data {int /*<<< orphan*/  max_bytes; } ;
struct filter {int /*<<< orphan*/  free_fn; int /*<<< orphan*/  filter_object_fn; struct filter_blobs_limit_data* filter_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_blobs_limit ; 
 int /*<<< orphan*/  free ; 
 struct filter_blobs_limit_data* xcalloc (int,int) ; 

__attribute__((used)) static void filter_blobs_limit__init(
	struct list_objects_filter_options *filter_options,
	struct filter *filter)
{
	struct filter_blobs_limit_data *d = xcalloc(1, sizeof(*d));
	d->max_bytes = filter_options->blob_limit_value;

	filter->filter_data = d;
	filter->filter_object_fn = filter_blobs_limit;
	filter->free_fn = free;
}