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
struct TYPE_3__ {int no_of_elements; } ;
typedef  TYPE_1__ queue ;

/* Variables and functions */

int get_no_of_elements(
	queue *my_queue
	)
{
	return my_queue->no_of_elements;
}