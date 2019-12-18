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
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  counter_u64_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ena_alloc_counters(counter_u64_t *begin, int size)
{
	counter_u64_t *end = (counter_u64_t *)((char *)begin + size);

	for (; begin < end; ++begin)
		*begin = counter_u64_alloc(M_WAITOK);
}