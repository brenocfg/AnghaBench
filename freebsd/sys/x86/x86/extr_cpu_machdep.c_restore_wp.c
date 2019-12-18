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
 int CR0_WP ; 
 int /*<<< orphan*/  load_cr0 (int) ; 
 int rcr0 () ; 

void
restore_wp(bool old_wp)
{

	if (old_wp)
		load_cr0(rcr0() | CR0_WP);
}