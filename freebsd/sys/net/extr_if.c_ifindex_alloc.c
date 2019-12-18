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
typedef  size_t u_short ;

/* Variables and functions */
 int /*<<< orphan*/  IFNET_WLOCK_ASSERT () ; 
 size_t USHRT_MAX ; 
 size_t V_if_index ; 
 size_t V_if_indexlim ; 
 int /*<<< orphan*/ ** V_ifindex_table ; 
 void* if_grow () ; 

__attribute__((used)) static u_short
ifindex_alloc(void **old)
{
	u_short idx;

	IFNET_WLOCK_ASSERT();
	/*
	 * Try to find an empty slot below V_if_index.  If we fail, take the
	 * next slot.
	 */
	for (idx = 1; idx <= V_if_index; idx++) {
		if (V_ifindex_table[idx] == NULL)
			break;
	}

	/* Catch if_index overflow. */
	if (idx >= V_if_indexlim) {
		*old = if_grow();
		return (USHRT_MAX);
	}
	if (idx > V_if_index)
		V_if_index = idx;
	return (idx);
}