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
 int /*<<< orphan*/  V_tcptw_zone ; 
 scalar_t__ maxtcptw ; 
 int /*<<< orphan*/  tcptw_auto_size () ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_tw_zone_change(void)
{

	if (maxtcptw == 0)
		uma_zone_set_max(V_tcptw_zone, tcptw_auto_size());
}