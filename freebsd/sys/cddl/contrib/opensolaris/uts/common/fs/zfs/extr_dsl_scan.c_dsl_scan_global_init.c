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
 int /*<<< orphan*/  fill_weight ; 
 int /*<<< orphan*/  zfs_scan_fill_weight ; 

void
dsl_scan_global_init(void)
{
	/*
	 * This is used in ext_size_compare() to weight segments
	 * based on how sparse they are. This cannot be changed
	 * mid-scan and the tree comparison functions don't currently
	 * have a mechansim for passing additional context to the
	 * compare functions. Thus we store this value globally and
	 * we only allow it to be set at module intiailization time
	 */
	fill_weight = zfs_scan_fill_weight;
}