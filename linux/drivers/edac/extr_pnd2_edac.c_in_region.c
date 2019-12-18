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
typedef  scalar_t__ u64 ;
struct region {scalar_t__ base; scalar_t__ limit; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */

__attribute__((used)) static bool in_region(struct region *rp, u64 addr)
{
	if (!rp->enabled)
		return false;

	return rp->base <= addr && addr <= rp->limit;
}