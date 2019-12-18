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
struct filter_trees_depth_data {int /*<<< orphan*/  seen_at_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct filter_trees_depth_data*) ; 
 int /*<<< orphan*/  oidmap_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void filter_trees_free(void *filter_data) {
	struct filter_trees_depth_data *d = filter_data;
	if (!d)
		return;
	oidmap_free(&d->seen_at_depth, 1);
	free(d);
}