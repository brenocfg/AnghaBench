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
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 scalar_t__ UCL_RANDOM_FUNCTION ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
ucl_hash_seed (void)
{
	static uint64_t seed;

	if (seed == 0) {
#ifdef UCL_RANDOM_FUNCTION
		seed = UCL_RANDOM_FUNCTION;
#else
		/* Not very random but can be useful for our purposes */
		seed = time (NULL);
#endif
	}

	return seed;
}