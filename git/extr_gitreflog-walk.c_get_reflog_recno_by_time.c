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
typedef  scalar_t__ timestamp_t ;
struct complete_reflogs {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {scalar_t__ timestamp; } ;

/* Variables and functions */

__attribute__((used)) static int get_reflog_recno_by_time(struct complete_reflogs *array,
	timestamp_t timestamp)
{
	int i;
	for (i = array->nr - 1; i >= 0; i--)
		if (timestamp >= array->items[i].timestamp)
			return i;
	return -1;
}