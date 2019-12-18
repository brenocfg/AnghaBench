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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NA (struct ifnet*) ; 
 scalar_t__ NM_NA_VALID (struct ifnet*) ; 
 int /*<<< orphan*/  netmap_set_all_rings (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
netmap_enable_all_rings(struct ifnet *ifp)
{
	if (NM_NA_VALID(ifp)) {
		netmap_set_all_rings(NA(ifp), 0 /* enabled */);
	}
}