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
typedef  size_t u32 ;
struct ti_sci_resource {size_t sets; TYPE_1__* desc; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */

u32 ti_sci_get_num_resources(struct ti_sci_resource *res)
{
	u32 set, count = 0;

	for (set = 0; set < res->sets; set++)
		count += res->desc[set].num;

	return count;
}