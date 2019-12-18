#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ priority; int generation; } ;
typedef  TYPE_1__ cam_pinfo ;

/* Variables and functions */

__attribute__((used)) static __inline int
queue_cmp(cam_pinfo **queue_array, int i, int j)
{
	if (queue_array[i]->priority == queue_array[j]->priority)
		return (  queue_array[i]->generation
			- queue_array[j]->generation );
	else
		return (  queue_array[i]->priority
			- queue_array[j]->priority );
}