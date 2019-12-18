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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fcmpset_long (scalar_t__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ vm_page_max_user_wired ; 
 scalar_t__ vm_user_wire_count ; 

__attribute__((used)) static bool
vm_map_wire_user_count_add(u_long npages)
{
	u_long wired;

	wired = vm_user_wire_count;
	do {
		if (npages + wired > vm_page_max_user_wired)
			return (false);
	} while (!atomic_fcmpset_long(&vm_user_wire_count, &wired,
	    npages + wired));

	return (true);
}