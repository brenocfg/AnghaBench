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
struct list_objects_filter_options {int /*<<< orphan*/  sparse_path_value; int /*<<< orphan*/  sparse_oid_value; int /*<<< orphan*/  filter_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 

void list_objects_filter_release(
	struct list_objects_filter_options *filter_options)
{
	free(filter_options->filter_spec);
	free(filter_options->sparse_oid_value);
	free(filter_options->sparse_path_value);
	memset(filter_options, 0, sizeof(*filter_options));
}