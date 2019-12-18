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
struct intel_raid_map {int stripe_count; int stripe_count_hi; } ;
typedef  int off_t ;

/* Variables and functions */

__attribute__((used)) static void
intel_set_map_stripe_count(struct intel_raid_map *mmap, off_t stripe_count)
{

	mmap->stripe_count = stripe_count & 0xffffffff;
	mmap->stripe_count_hi = stripe_count >> 32;
}