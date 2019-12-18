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

/* Variables and functions */
 int test_bit (unsigned int,unsigned long*) ; 

__attribute__((used)) static bool regcache_reg_present(unsigned long *cache_present, unsigned int idx)
{
	if (!cache_present)
		return true;

	return test_bit(idx, cache_present);
}