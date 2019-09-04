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
struct list_objects_filter_options {int no_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_objects_filter_release (struct list_objects_filter_options*) ; 

__attribute__((used)) static inline void list_objects_filter_set_no_filter(
	struct list_objects_filter_options *filter_options)
{
	list_objects_filter_release(filter_options);
	filter_options->no_filter = 1;
}