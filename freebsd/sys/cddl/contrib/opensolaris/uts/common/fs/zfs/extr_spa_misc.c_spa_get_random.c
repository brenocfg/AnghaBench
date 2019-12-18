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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  random_get_pseudo_bytes (void*,int) ; 

uint64_t
spa_get_random(uint64_t range)
{
	uint64_t r;

	ASSERT(range != 0);

	(void) random_get_pseudo_bytes((void *)&r, sizeof (uint64_t));

	return (r % range);
}