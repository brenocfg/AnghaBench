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
struct range_set {scalar_t__ nr; scalar_t__ alloc; int /*<<< orphan*/ * ranges; } ;

/* Variables and functions */
 int /*<<< orphan*/  range_set_release (struct range_set*) ; 

__attribute__((used)) static void range_set_move(struct range_set *dst, struct range_set *src)
{
	range_set_release(dst);
	dst->ranges = src->ranges;
	dst->nr = src->nr;
	dst->alloc = src->alloc;
	src->ranges = NULL;
	src->alloc = src->nr = 0;
}