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
struct commit_list {TYPE_1__* item; } ;
struct TYPE_2__ {scalar_t__ date; } ;

/* Variables and functions */

__attribute__((used)) static int commit_list_compare_by_date(const void *a, const void *b)
{
	timestamp_t a_date = ((const struct commit_list *)a)->item->date;
	timestamp_t b_date = ((const struct commit_list *)b)->item->date;
	if (a_date < b_date)
		return 1;
	if (a_date > b_date)
		return -1;
	return 0;
}