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
struct timeval {int dummy; } ;
struct timehist {size_t num; TYPE_1__* buckets; } ;
struct TYPE_2__ {int /*<<< orphan*/  count; int /*<<< orphan*/  upper; } ;

/* Variables and functions */
 scalar_t__ timeval_smaller (struct timeval*,int /*<<< orphan*/ *) ; 

void timehist_insert(struct timehist* hist, struct timeval* tv)
{
	size_t i;
	for(i=0; i<hist->num; i++) {
		if(timeval_smaller(tv, &hist->buckets[i].upper)) {
			hist->buckets[i].count++;
			return;
		}
	}
	/* dump in last bucket */
	hist->buckets[hist->num-1].count++;
}