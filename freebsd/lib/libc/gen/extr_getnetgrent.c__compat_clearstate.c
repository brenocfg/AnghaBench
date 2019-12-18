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
 scalar_t__ _netgr_yp_enabled ; 
 int /*<<< orphan*/  compat_state ; 
 int /*<<< orphan*/  netgr_endstate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
_compat_clearstate(void)
{

#ifdef YP
	_netgr_yp_enabled = 0;
#endif
	netgr_endstate(&compat_state);
}