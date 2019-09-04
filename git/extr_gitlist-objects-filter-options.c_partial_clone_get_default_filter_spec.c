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

/* Variables and functions */
 int /*<<< orphan*/  core_partial_clone_filter_default ; 
 int /*<<< orphan*/  gently_parse_list_objects_filter (struct list_objects_filter_options*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void partial_clone_get_default_filter_spec(
	struct list_objects_filter_options *filter_options)
{
	/*
	 * Parse default value, but silently ignore it if it is invalid.
	 */
	if (!core_partial_clone_filter_default)
		return;
	gently_parse_list_objects_filter(filter_options,
					 core_partial_clone_filter_default,
					 NULL);
}