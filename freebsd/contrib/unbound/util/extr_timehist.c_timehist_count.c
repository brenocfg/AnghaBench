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
struct timehist {size_t num; TYPE_1__* buckets; } ;
struct TYPE_2__ {scalar_t__ count; } ;

/* Variables and functions */

__attribute__((used)) static size_t
timehist_count(struct timehist* hist)
{
	size_t i, res = 0;
	for(i=0; i<hist->num; i++)
		res += hist->buckets[i].count;
	return res;
}