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
struct ifnet {int /*<<< orphan*/  if_vnet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET_QUIET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_detach_internal (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
if_detach(struct ifnet *ifp)
{

	CURVNET_SET_QUIET(ifp->if_vnet);
	if_detach_internal(ifp, 0, NULL);
	CURVNET_RESTORE();
}