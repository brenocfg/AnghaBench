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
typedef  long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  geode_counter ; 
 unsigned int inl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
geode_cputicks(void)
{
	unsigned c;
	static unsigned last;
	static uint64_t offset;

	c = inl(geode_counter);
	if (c < last)
		offset += (1LL << 32);
	last = c;
	return (offset | c);
}