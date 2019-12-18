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
 size_t V_if_index ; 
 int /*<<< orphan*/ ** V_ifindex_table ; 

__attribute__((used)) static void
ifindex_free_locked(u_short idx)
{

	IFNET_WLOCK_ASSERT();

	V_ifindex_table[idx] = NULL;
	while (V_if_index > 0 &&
	    V_ifindex_table[V_if_index] == NULL)
		V_if_index--;
}