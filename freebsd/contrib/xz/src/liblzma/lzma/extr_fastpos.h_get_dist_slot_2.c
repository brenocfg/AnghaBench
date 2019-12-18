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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ FULL_DISTANCES ; 
 scalar_t__ FULL_DISTANCES_BITS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fastpos_limit (scalar_t__,int) ; 
 scalar_t__ fastpos_result (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static inline uint32_t
get_dist_slot_2(uint32_t dist)
{
	assert(dist >= FULL_DISTANCES);

	if (dist < fastpos_limit(FULL_DISTANCES_BITS - 1, 0))
		return fastpos_result(dist, FULL_DISTANCES_BITS - 1, 0);

	if (dist < fastpos_limit(FULL_DISTANCES_BITS - 1, 1))
		return fastpos_result(dist, FULL_DISTANCES_BITS - 1, 1);

	return fastpos_result(dist, FULL_DISTANCES_BITS - 1, 2);
}