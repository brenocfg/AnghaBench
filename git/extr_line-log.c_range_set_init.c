#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct range_set {int /*<<< orphan*/ * ranges; scalar_t__ nr; scalar_t__ alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  range_set_grow (struct range_set*,size_t) ; 

void range_set_init(struct range_set *rs, size_t prealloc)
{
	rs->alloc = rs->nr = 0;
	rs->ranges = NULL;
	if (prealloc)
		range_set_grow(rs, prealloc);
}