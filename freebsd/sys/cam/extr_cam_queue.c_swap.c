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
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ cam_pinfo ;

/* Variables and functions */

__attribute__((used)) static __inline void
swap(cam_pinfo **queue_array, int i, int j)
{
	cam_pinfo *temp_qentry;

	temp_qentry = queue_array[j];
	queue_array[j] = queue_array[i];
	queue_array[i] = temp_qentry;
	queue_array[j]->index = j;
	queue_array[i]->index = i;
}