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
struct range_set {size_t nr; TYPE_1__* ranges; } ;
struct TYPE_2__ {long start; long end; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  range_set_grow (struct range_set*,int) ; 

void range_set_append_unsafe(struct range_set *rs, long a, long b)
{
	assert(a <= b);
	range_set_grow(rs, 1);
	rs->ranges[rs->nr].start = a;
	rs->ranges[rs->nr].end = b;
	rs->nr++;
}