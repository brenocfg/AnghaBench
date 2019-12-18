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
 int /*<<< orphan*/  __pciwb_mio () ; 
 int /*<<< orphan*/  have_mio ; 
 scalar_t__ static_branch_likely (int /*<<< orphan*/ *) ; 

void zpci_barrier(void)
{
	if (static_branch_likely(&have_mio))
		__pciwb_mio();
}