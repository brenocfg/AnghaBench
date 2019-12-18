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
struct ifnet {int if_capabilities; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */

int
if_setcapabilitiesbit(if_t ifp, int setbit, int clearbit)
{
	((struct ifnet *)ifp)->if_capabilities |= setbit;
	((struct ifnet *)ifp)->if_capabilities &= ~clearbit;

	return (0);
}