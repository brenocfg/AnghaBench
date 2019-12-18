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
struct list_objects_filter_options {int dummy; } ;
struct filter {int /*<<< orphan*/  free_fn; int /*<<< orphan*/  filter_object_fn; } ;

/* Variables and functions */
 int /*<<< orphan*/  filter_blobs_none ; 
 int /*<<< orphan*/  free ; 

__attribute__((used)) static void filter_blobs_none__init(
	struct list_objects_filter_options *filter_options,
	struct filter *filter)
{
	filter->filter_object_fn = filter_blobs_none;
	filter->free_fn = free;
}