#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* dd_parent; } ;
typedef  TYPE_1__ dsl_dir_t ;

/* Variables and functions */

__attribute__((used)) static dsl_dir_t *
closest_common_ancestor(dsl_dir_t *ds1, dsl_dir_t *ds2)
{
	for (; ds1; ds1 = ds1->dd_parent) {
		dsl_dir_t *dd;
		for (dd = ds2; dd; dd = dd->dd_parent) {
			if (ds1 == dd)
				return (dd);
		}
	}
	return (NULL);
}